#include "MyForm.h"
//OpenGL
#include<GL\glew.h>
#include<GL\GL.h>
#include<GL\GLU.h>
#include<GL\freeglut.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>
//STD
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#include "Simulation.h"
#include "CellularAutomata.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	GDMwGB::MyForm form;
	Application::Run(%form);
}

unsigned int VBO, VAO, EBO, colorVBO, translationsVBO;
int shaderProgram;
static glm::mat4    projection,
					model,
					view;

static GLuint		modelLoc,
					viewLoc,
					projLoc,
					lightPosLoc;
static int m, n, o;

glm::vec3 * colors;
glm::vec3 * translations;

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		//getchar();
		return 0;
	}
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);
	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		//printf("%s\n", &VertexShaderErrorMessage[0]);
		std::string Error(VertexShaderErrorMessage.begin(), VertexShaderErrorMessage.end());
		if(Error.size() != 13)
			MessageBox::Show(gcnew String(Error.c_str()),
				"VertexShader Error", MessageBoxButtons::YesNo,
				MessageBoxIcon::Question);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);
	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		//printf("%s\n", &FragmentShaderErrorMessage[0]);
		std::string Error(FragmentShaderErrorMessage.begin(), FragmentShaderErrorMessage.end());
		if (Error.size() != 13)
			MessageBox::Show(gcnew String(Error.c_str()),
				"FragmentShader Error", MessageBoxButtons::YesNo,
				MessageBoxIcon::Question);
	}
	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		//printf("%s\n", &ProgramErrorMessage[0]);
		std::string Error(ProgramErrorMessage.begin(), ProgramErrorMessage.end());
		if (Error.size() != 13)
			MessageBox::Show(gcnew String(Error.c_str()),
				"Program Error", MessageBoxButtons::YesNo,
				MessageBoxIcon::Question);
	}
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}

System::Void GDMwGB::MyForm::OpenGLInit(System::Object ^ sender, System::EventArgs ^ e)
{
	colors = new glm::vec3[m * n * o];
	// Tablica bufora przeniesien
	translations = new glm::vec3[m * n * o];

	//inicjacja GLEW
	glewExperimental = true;
	glewInit();
	//
	m = this->simulation->cellularautomata->getSize()[0];
	n = this->simulation->cellularautomata->getSize()[1];
	o = this->simulation->cellularautomata->getSize()[2];
	//TODO:: Intel Graphic nie obsluguje per instance
	// Tablica bufora kolorow
	colors = new glm::vec3[ m * n * o];
	// Tablica bufora przeniesien
	translations = new glm::vec3[ m * n * o];
	
	int index = 0;
	for (int i = 0 ; i < m; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < o; k++) //for (int l = 0;l < 36; l++) // TODO:: petla wylacznie dla Intel
				{
					if (this->simulation->cellularautomata->getCells()[i][j][k].getState() == 0)
					{
						colors[index] = glm::vec3(1.f, 1.f, 1.f);
					}
					else if (this->simulation->cellularautomata->getCells()[i][j][k].getState() == 1)
					{
						colors[index] = glm::vec3(0.0f, 0.5f, 0.5f);
					}
					else if (this->simulation->cellularautomata->getCells()[i][j][k].getState() == 2)
					{
						colors[index] = glm::vec3(0.40f, 0.5f, 0.f);
					}
					translations[index] = glm::vec3((float) i, (float)j, (float)k);
					index++;
				}
	// Create and compile our GLSL program from the shaders
	shaderProgram = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
	//Import lokacji uniformów
	modelLoc      =	glGetUniformLocation(shaderProgram, "model");
	viewLoc       =	glGetUniformLocation(shaderProgram, "view");
	projLoc       =	glGetUniformLocation(shaderProgram, "projection");
	lightPosLoc   =	glGetUniformLocation(shaderProgram, "lightPos");
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glm::vec3 * col = colors;
	
	// Store instance data in an array buffer
	glGenBuffers(1, &translationsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, translationsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * n * m * o, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * n * m * o, &colors[0], GL_DYNAMIC_DRAW); // TODO:: 36 tylko dla Intel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glGenVertexArrays(1, &VAO);													// Twozenie Vertex Array Object
	glGenBuffers(1, &VBO);														// Twozenie Vertex Buffer Object
	glBindVertexArray(VAO);														// Konfiguracja Vertex Array Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);											// Gneracja tablicy Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Przypisanie wieszcho³ków do Vertex Buffer Object
	//Konfiguracja 0 atrybutu
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	
	// normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	//Konfiguracja 1 atrybutu [ Kolor ]
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);

	//Konfiguracja 1 atrybutu [ Przeniesienie ]
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, translationsVBO);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(3, 1);
	glBindVertexArray(0);
	// TODO: je¿eli nie obsluguje layout
	//glBindAttribLocation(shaderProgram, 0, "position");
	//glBindAttribLocation(shaderProgram, 2, "normal");
	//glBindAttribLocation(shaderProgram, 1, "color");
	//glBindAttribLocation(shaderProgram, 3, "translation");

	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO); 
	
	
	// Konfiguracja uniformu mvp
	projection = glm::perspective(45.0f, (GLfloat)this->openGLControl1->Width / this->openGLControl1->Height, 0.1f, 100000.0f);
	view =	glm::lookAt(glm::vec3(((GLfloat)n / 2), ((GLfloat)m / 2), ((GLfloat)o / 2)),
						glm::vec3(((GLfloat)n / 2), ((GLfloat)m / 2), ((GLfloat)o / 2)),
						glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::mat4();
	// Przsylanie uniformów
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//Wlaczenie Depth Test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return System::Void();
}

System::Void GDMwGB::MyForm::OpenGLRender(System::Object ^ sender, System::EventArgs ^ e)
{
	// Czyszczenie obrazu
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Kamera
	float radius = m;
	if (n > radius) radius = n;
	if (o > radius) radius = o;
	float r = radius  * camera->getScale();
	GLfloat camX = cos(glm::radians(camera->getBetaRotation())) * cos(glm::radians(camera->getAlphaRotation()));
	GLfloat camY = sin(glm::radians(camera->getBetaRotation()));
	GLfloat camZ = cos(glm::radians(camera->getBetaRotation())) * sin(glm::radians(camera->getAlphaRotation()));
	view = glm::lookAt(glm::vec3((GLfloat)(n - 1) / 2 + (r * camX), (GLfloat)(m - 1) / 2 + (r *camY), (GLfloat)(o - 1) / 2 + (r * camZ)),
						glm::vec3((GLfloat)(n - 1) / 2, (GLfloat)(m - 1) / 2, (GLfloat)(o - 1) / 2),
						glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform3f(lightPosLoc, ((GLfloat)(n - 1) / 2) + ( (radius + 100) * camX), ((GLfloat)(m - 1) / 2) + ((radius + 100) * camY), ((GLfloat)(o - 1) / 2) + ((radius + 100) *camZ));

	///
	int index = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < o; k++) //for (int l = 0;l < 36; l++) // TODO:: petla wylacznie dla Intel
			{
				unsigned int s = 0;
				s = this->simulation->cellularautomata->getCells()[i][j][k].getState();
				if (s == 0)
				{
					colors[index] = glm::vec3(1.f, 1.f, 1.f);
				}
				else if (s == 1)
				{
					colors[index] = glm::vec3(1.f, 0.f, 0.f);
				}
				else if (s == 2)
				{
					colors[index] = glm::vec3(0.f, 1.f, 0.f);
				}
				translations[index] = glm::vec3((float)i, (float)j, (float)k);
				index++;
			}
		}
	}
		
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * n * m * o, &colors[0], GL_DYNAMIC_DRAW); // TODO:: 36 tylko dla Intel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shaderProgram);
	// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glBindVertexArray(VAO); 
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, n * m * o);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	return System::Void();
}

System::Void GDMwGB::MyForm::OpenGLResize(System::Object ^ sender, System::EventArgs ^ e)
{
	glViewport(0, 0, (GLsizei)openGLControl1->Width, (GLsizei)openGLControl1->Height);
	projection = glm::perspective(45.0f, (GLfloat)this->openGLControl1->Width / this->openGLControl1->Height, 0.1f, 100000.0f);
	return System::Void();
}

System::Void GDMwGB::MyForm::MouseWheel(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	camera->setScale( camera->getScale() + ((-1 * e->Delta) / abs(e->Delta) ) );
	return System::Void();
}

System::Void GDMwGB::MyForm::MouseDown(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	mouse->setPressed(true);
	mouse->setLastX(e->X);
	mouse->setLastY(e->Y);
	return System::Void();
}

System::Void GDMwGB::MyForm::MouseMove(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	if (mouse->isPressed())
	{
		float deltaX = (float)(e->X - mouse->getLastX());
		float deltaY = (float)(e->Y - mouse->getLastY());

		camera->setAlphaRotation(camera->getAlphaRotation() + deltaX);
		camera->setBetaRotation(camera->getBetaRotation() + deltaY);

		mouse->setLastX(e->X);
		mouse->setLastY(e->Y);
	}
	return System::Void();
}

System::Void GDMwGB::MyForm::MouseUp(System::Object ^ sender, System::Windows::Forms::MouseEventArgs ^ e)
{
	mouse->setPressed(false);
	return System::Void();
}

System::Void GDMwGB::MyForm::MainForm_Resize(System::Object ^ sender, System::EventArgs ^ e)
{
	/*int newX = this->openGLControl1->Width + (this->Width - this->oldWindowSize.Width),
		newY = this->openGLControl1->Height + (this->Height - this->oldWindowSize.Height);*/
	this->openGLControl1->Width += (this->Width - this->oldWindowSize.Width);
	this->openGLControl1->Height += (this->Height - this->oldWindowSize.Height);

	this->oldWindowSize = this->Size;
	//this->openGLControl1->SetSize
	return System::Void();
}

System::Void GDMwGB::MyForm::Simulate_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	this->simulation->step();
	return System::Void();
}

System::Void GDMwGB::MyForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	// no smaller than design time size
	
	this->MinimumSize = System::Drawing::Size(640, 480);

	// no larger than screen size
	this->MaximumSize = System::Drawing::Size(Screen::PrimaryScreen->Bounds.Width, Screen::PrimaryScreen->Bounds.Width);
		//System::Drawing::Size(Screen::PrimaryScreen::Bounds::Width, Screen.PrimaryScreen.Bounds.Height, (int)System.Windows.SystemParameters.PrimaryScreenHeight);
	return System::Void();
}

