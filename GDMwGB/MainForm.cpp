#include "MainForm.h"
//OpenGL
#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\freeglut.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/type_ptr.hpp>
//STD
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Simulation.h"
#include "GrainGrowthSimulation.h"
#include "CellularAutomata.h"
#include "NucleonGenerator.h"
#include "MooreNeighborhood.h"
#include "VonNeummanNeighborhood.h"
#include "PentagonalNeighborhood.h"
#include "HexagonalNeighborhood.h"

#include "Calculations.h"

#include "MyNewForm.h"

#include "NewForm.h"


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

bool draw = true;

GLuint GDMwGB::MyForm::LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {
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
	//inicjacja GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) return;
	//
	while (!this->simulation && colorFactory->count <= 1)
	{

	}
	Simulation * sim = new Simulation(*this->simulation);

	int	m = sim->cellularautomata->getSize()[0],
		n = sim->cellularautomata->getSize()[1],
		o = sim->cellularautomata->getSize()[2];
	if (!this->colorFactory)
	{
		this->colorFactory->generate(n*m*o);
	}

	std::vector<glm::vec3> vcolors;
	std::vector<glm::vec3> vtranslations;

	
	vcolors.push_back(glm::vec3(1.f, 1.f, 1.f));
	vtranslations.push_back( glm::vec3(1.f, 1.f, 1.f));
				

	colors = new glm::vec3[vcolors.size()];
	// Tablica bufora przeniesien
	translations = new glm::vec3[vtranslations.size()];

	for (int i = 0; i < vcolors.size(); i++)
	{
		colors[i] = vcolors[i];
		translations[i] = vtranslations[i];
	}
	
	/*int index = 0;*/
	//for (int i = 0 ; i < m; i++)
	//	for (int j = 0; j < n; j++)
	//		for (int k = 0; k < o; k++) //for (int l = 0;l < 36; l++) // TODO:: petla wylacznie dla Intel
	//			{
	//				colors[index] = glm::vec3(1.f, 1.f, 1.f);
	//				translations[index] = glm::vec3((float) i, (float)j, (float)k);
	//				index++;
	//			}
	
	// Create and compile our GLSL program from the shaders
	shaderProgram[0] = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
	shaderProgram[1] = LoadShaders("TransformVertexShader.vertexshader", "NoGrainFragmentShader.fragmentshader");
	shaderProgram[2] = LoadShaders("TransformVertexShader.vertexshader", "NoGrainBoundaryFragmentShader.fragmentshader");
	shaderIndex = 0;
	//Import lokacji uniformów
	modelLoc      =	glGetUniformLocation(shaderProgram[shaderIndex], "model");
	viewLoc       =	glGetUniformLocation(shaderProgram[shaderIndex], "view");
	projLoc       =	glGetUniformLocation(shaderProgram[shaderIndex], "projection");
	lightPosLoc   =	glGetUniformLocation(shaderProgram[shaderIndex], "lightPos");
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
	glGenBuffers(1, translationsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *translationsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vtranslations.size(), &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, *colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vcolors.size(), &colors[0], GL_DYNAMIC_DRAW); // TODO:: 36 tylko dla Intel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glGenVertexArrays(1, VAO);													// Twozenie Vertex Array Object
	glGenBuffers(1, VBO);														// Twozenie Vertex Buffer Object
	glBindVertexArray(*VAO);														// Konfiguracja Vertex Array Object
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);											// Gneracja tablicy Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// Przypisanie wieszcho³ków do Vertex Buffer Object
	//Konfiguracja 0 atrybutu
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	
	// normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	
	//Konfiguracja 1 atrybutu [ Kolor ]
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, *colorVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);

	//Konfiguracja 1 atrybutu [ Przeniesienie ]
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, *translationsVBO);
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
	*projection = glm::perspective(45.0f, (GLfloat)this->openGLControl1->Width / this->openGLControl1->Height, 0.1f, 100000.0f);
	*view = glm::lookAt(glm::vec3(((GLfloat)n / 2), ((GLfloat)m / 2), ((GLfloat)o / 2)),
						glm::vec3(((GLfloat)n / 2), ((GLfloat)m / 2), ((GLfloat)o / 2)),
						glm::vec3(0.0f, 1.0f, 0.0f));
	model = new glm::mat4();
	// Przsylanie uniformów
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(*projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(*model));
	//Wlaczenie Depth Test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return System::Void();
}

System::Void GDMwGB::MyForm::OpenGLRender(System::Object ^ sender, System::EventArgs ^ e)
{
	Simulation * sim = new Simulation(*this->simulation);

	std::vector<glm::vec3> vcolors;
	std::vector<glm::vec3> vtranslations;

	// Czyszczenie obrazu
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Kamera
	this->camera->x0 = 0;
	this->camera->x1 = sim->cellularautomata->getSize()[0] - 1;
	this->camera->y0 = 0;
	this->camera->y1 = sim->cellularautomata->getSize()[1] - 1;
	this->camera->z0 = 0;
	this->camera->z1 = sim->cellularautomata->getSize()[2] - 1;


	int	m = sim->cellularautomata->getSize()[0],
		n = sim->cellularautomata->getSize()[1],
		o = sim->cellularautomata->getSize()[2];

	float radius = m;
	if (n > radius) radius = n;
	if (o > radius) radius = o;
	float r = radius  * camera->getScale();
	GLfloat camX = sin(glm::radians(camera->getBetaRotation()));
	GLfloat camY = cos(glm::radians(camera->getBetaRotation())) * cos(glm::radians(camera->getAlphaRotation()));
	GLfloat camZ = cos(glm::radians(camera->getBetaRotation())) * sin(glm::radians(camera->getAlphaRotation()));
	*view = glm::lookAt(glm::vec3((((GLfloat)m - 1.f) / 2) + (r * camY), (((GLfloat)n - 1.f) / 2) + (r *camX), (((GLfloat)o - 1.f) / 2) + (r * camZ)),
		glm::vec3((((GLfloat)m - 1.f) / 2), (((GLfloat)n - 1.f) / 2), (((GLfloat)o - 1.f) / 2)),
		glm::vec3(0.0f, 1.0f, 0.0f));

	modelLoc = glGetUniformLocation(shaderProgram[shaderIndex], "model");
	viewLoc = glGetUniformLocation(shaderProgram[shaderIndex], "view");
	projLoc = glGetUniformLocation(shaderProgram[shaderIndex], "projection");
	lightPosLoc = glGetUniformLocation(shaderProgram[shaderIndex], "lightPos");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(*projection));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(*model));
	glUniform3f(lightPosLoc, ((GLfloat)(m - 1) / 2) + ((radius + 100) * camY), ((GLfloat)(n - 1) / 2) + ((radius + 100) * camX), ((GLfloat)(o - 1) / 2) + ((radius + 100) *camZ));

	///
	if (this->comboBoxView->SelectedIndex == 0)
	{
		for (int i = camera->x0; i <= camera->x1; i++)
		{
			for (int j = camera->y0; j <= camera->y1; j++)
			{
				#pragma region Calc
				unsigned int s = 0;
				s = sim->cellularautomata->getCells()[i][j][camera->z0].getState();
				if(sim->cellularautomata->getCells()[i][j][camera->z0].getState() <= sim->cellularautomata->nucleons_count + 2)
					vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
												this->colorFactory->colors[s].g, 
												this->colorFactory->colors[s].b));
				else
					vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count/2) + s].r,
												this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
												this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));

				vtranslations.push_back(glm::vec3((float)i, (float)j, (float)camera->z0));
				#pragma endregion
			}
		}
		for (int i = camera->x0; i <= camera->x1; i++)
		{
			for (int j = camera->y0; j <= camera->y1; j++)
			{
				#pragma region Calc
				unsigned int s = 0;
				s = sim->cellularautomata->getCells()[i][j][camera->z1].getState();
				if (sim->cellularautomata->getCells()[i][j][camera->z1].getState() <= sim->cellularautomata->nucleons_count + 2)
					vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
						this->colorFactory->colors[s].g,
						this->colorFactory->colors[s].b));
				else
					vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count / 2) + s].r,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));
				vtranslations.push_back(glm::vec3((float)i, (float)j, (float)camera->z1));
				#pragma endregion
			}
		}

		for (int i = camera->x0; i <= camera->x1; i++)
		{
			for (int k = camera->z0; k <= camera->z1; k++)
			{
				#pragma region Calc
				unsigned int s = 0;
				s = sim->cellularautomata->getCells()[i][camera->y0][k].getState();
				if (sim->cellularautomata->getCells()[i][camera->y0][k].getState() <= sim->cellularautomata->nucleons_count + 2)
					vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
						this->colorFactory->colors[s].g,
						this->colorFactory->colors[s].b));
				else
					vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count / 2) + s].r,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));

				vtranslations.push_back( glm::vec3((float)i, (float)camera->y0, (float)k));
				#pragma endregion
			}
		}
		for (int i = camera->x0; i <= camera->x1; i++)
		{
			for (int k = camera->z0; k < camera->z1; k++)
			{
				#pragma region Calc
				unsigned int s = 0;
				s = sim->cellularautomata->getCells()[i][camera->y1][k].getState();
				if (sim->cellularautomata->getCells()[i][camera->y1][k].getState() <= sim->cellularautomata->nucleons_count + 2)
					vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
						this->colorFactory->colors[s].g,
						this->colorFactory->colors[s].b));
				else
					vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count / 2) + s].r,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));
				vtranslations.push_back(glm::vec3((float)i, (float)camera->y1, (float)k));
				#pragma endregion
			}
		}

		for (int j = camera->y0 + 1; j <= camera->x1 - 1; j++)
		{
			for (int k = camera->z0 + 1; k <= camera->z1 - 1; k++)
			{
				#pragma region Calc
				unsigned int s = 0;
				s = sim->cellularautomata->getCells()[camera->x0][j][k].getState();
				if (sim->cellularautomata->getCells()[camera->x0][j][k].getState() <= sim->cellularautomata->nucleons_count + 2)
					vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
						this->colorFactory->colors[s].g,
						this->colorFactory->colors[s].b));
				else
					vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count / 2) + s].r,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));
				vtranslations.push_back(glm::vec3((float)camera->x0, (float)j, (float)k));
				#pragma endregion
			}
		}
		for (int j = camera->y0 + 1; j <= camera->x1 - 1; j++)
		{
			for (int k = camera->z0 + 1; k <= camera->z1 - 1; k++)
			{
				#pragma region Calc
				unsigned int s = 0;
				s = sim->cellularautomata->getCells()[camera->x1][j][k].getState();
				if (sim->cellularautomata->getCells()[camera->x1][j][k].getState() <= sim->cellularautomata->nucleons_count + 2)
					vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
						this->colorFactory->colors[s].g,
						this->colorFactory->colors[s].b));
				else
					vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count / 2) + s].r,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
						this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));
				vtranslations.push_back(glm::vec3((float)camera->x1, (float)j, (float)k));
				#pragma endregion
			}
		}
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < o; k++) //for (int l = 0;l < 36; l++) // TODO:: petla wylacznie dla Intel
				{
					unsigned int s = 0;
					s = sim->cellularautomata->getCells()[i][j][k].getState();
					if (sim->cellularautomata->getCells()[i][j][k].getState() <= sim->cellularautomata->nucleons_count + 2)
						vcolors.push_back(glm::vec3(this->colorFactory->colors[s].r,
							this->colorFactory->colors[s].g,
							this->colorFactory->colors[s].b));
					else
						vcolors.push_back(glm::vec3(this->colorFactory->colors[(this->colorFactory->count / 2) + s].r,
							this->colorFactory->colors[(this->colorFactory->count / 2) + s].g,
							this->colorFactory->colors[(this->colorFactory->count / 2) + s].b));
					vtranslations.push_back(glm::vec3((float)i, (float)j, (float)k));
				}
			}
		}
	}
	
	if (colors) delete[] colors;
	if (translations) delete[] translations;

	colors = new glm::vec3[vcolors.size()];
	translations = new glm::vec3[vtranslations.size()];
	for (int i =0;i<vcolors.size();i++)
	{
		colors[i] = vcolors[i];
		translations[i] = vtranslations[i];
	}

	//int size = (m*n*o) - (m-1*n-1*o-1);
	glBindBuffer(GL_ARRAY_BUFFER, *colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) *vcolors.size(), &colors[0], GL_DYNAMIC_DRAW); // TODO:: 36 tylko dla starych Intel Graphic
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, *translationsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vtranslations.size(), &translations[0], GL_DYNAMIC_DRAW); // TODO:: 36 tylko dla Intel dla starych Intel Graphic
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(shaderProgram[shaderIndex]);
	// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glBindVertexArray(*VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, vcolors.size());
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	return System::Void();
}

System::Void GDMwGB::MyForm::OpenGLResize(System::Object ^ sender, System::EventArgs ^ e)
{
	glViewport(0, 0, (GLsizei)openGLControl1->Width, (GLsizei)openGLControl1->Height);
	*projection = glm::perspective(45.0f, (GLfloat)this->openGLControl1->Width / this->openGLControl1->Height, 0.1f, 100000.0f);
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
	c->simulation = this->simulation;
	if (this->calculationThread)
	{
		if (this->calculationThread->ThreadState != System::Threading::ThreadState::Running)
		{
			delete this->calculationThread;
		}
		else return System::Void();
	}

	this->calculationThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(c, &Calculations::simulate));
	this->calculationThread->Start();
	
	//this->simulation->start();
	//this->simulation->step();
	return System::Void();
}

System::Void GDMwGB::MyForm::NewMenuButton(System::Object ^ sender, System::EventArgs ^ e)
{
	NewForm Form;
	Form.ShowDialog();
	if (Form.Done)
	{
		this->simulation->cellularautomata = new CellularAutomata((int)Form.XNumericUpDown->Value, (int)Form.YNumericUpDown->Value, (int)Form.ZNumericUpDown->Value);
	}

	int	m = this->simulation->cellularautomata->getSize()[0],
		n = this->simulation->cellularautomata->getSize()[1],
		o = this->simulation->cellularautomata->getSize()[2];
	if (this->colorFactory->count < (n*m*o))
	{
		this->colorFactory->generate(n*m*o);
	}
	

	//TODO:: Intel Graphic nie obsluguje per instance
	// Tablica bufora kolorow

	colors = new glm::vec3[m * n * o];
	// Tablica bufora przeniesien
	translations = new glm::vec3[m * n * o];

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
					colors[index] = glm::vec3(0.f, 0.f, 0.f);
				}
				else if (s == 2)
				{
					colors[index] = glm::vec3(0.7f, 1.f, 0.1f);
				}
				else if (s == 3)
				{
					colors[index] = glm::vec3(0.3f, 1.f, 0.3f);
				}
				translations[index] = glm::vec3((float)i, (float)j, (float)k);
				index++;
			}
		}
	}
	
	///Powiekszenie buforow na kracie graf.
	//glDeleteVertexArrays(1, VAO);
	// Usuwanie starego buffora
	//glDeleteBuffers(1, VBO);
	//glDeleteBuffers(1, colorVBO);
	//glDeleteBuffers(1, translationsVBO);
	

	
	//this->OpenGLInit(nullptr, nullptr);
	// Tworzenie nowych bufforow
	//glGenBuffers(1, translationsVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, *translationsVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * n * m * o, &translations[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	////glGenBuffers(1, colorVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, *colorVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * n * m * o, &colors[0], GL_DYNAMIC_DRAW); // TODO:: 36 tylko dla Intel
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	return System::Void();
}

System::Void GDMwGB::MyForm::ExitMenuButton(System::Object ^ sender, System::EventArgs ^ e)
{
	System::Windows::Forms::DialogResult dr;
	dr = MessageBox::Show("Czy chcesz wyjœæ z aplikacji?","GDMwGB",System::Windows::Forms::MessageBoxButtons::YesNo);
	if (dr == System::Windows::Forms::DialogResult::Yes)
	{
		this->Close();
	}
	return System::Void();
}

System::Void GDMwGB::MyForm::NeighborhoodChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (this->comboBoxNeighborhood->SelectedIndex == 0)
	{
		if(this->simulation->neighborhood) delete this->simulation->neighborhood;
		this->simulation->neighborhood = new MooreNeighborhood();
	}
	else if (this->comboBoxNeighborhood->SelectedIndex == 1)
	{
		if (this->simulation->neighborhood) delete this->simulation->neighborhood;
		this->simulation->neighborhood = new VonNeummanNeighborhood();
	}
	else if (this->comboBoxNeighborhood->SelectedIndex == 2)
	{
		if (this->simulation->neighborhood) delete this->simulation->neighborhood;
		this->simulation->neighborhood = new PentagonalNeighborhood();
	}
	else if (this->comboBoxNeighborhood->SelectedIndex == 3)
	{
		if (this->simulation->neighborhood) delete this->simulation->neighborhood;
		this->simulation->neighborhood = new HexagonalNeighborhood();
	}
	return System::Void();
}

System::Void GDMwGB::MyForm::SimulationChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (this->comboBoxSymulation->SelectedIndex == 0)
	{
		Simulation * newSim = new GrainGrowthSimulation();
		if (this->simulation)
		{
			newSim->cellularautomata = this->simulation->cellularautomata;
			delete this->simulation;
		}
		this->simulation = newSim;
	}
	else if (this->comboBoxSymulation->SelectedIndex == 1)
	{
		Simulation * newSim = new GrainBoundarySimulation();
		if (this->simulation)
		{
			newSim->cellularautomata = this->simulation->cellularautomata;
			delete this->simulation;
		}
		this->simulation = newSim;
	}
	/*this->simulation->cellularautomata->getCells()[(this->simulation->cellularautomata->getSize()[0] - 1) / 2][(this->simulation->cellularautomata->getSize()[1] - 1) / 2][0].setState(3);
	this->simulation->cellularautomata->getCells()[(this->simulation->cellularautomata->getSize()[0] - 1) / 2][(this->simulation->cellularautomata->getSize()[1] - 1) / 2][this->simulation->cellularautomata->getSize()[2] - 1].setState(4);
	this->simulation->cellularautomata->nucleon_count += 2;*/
	this->comboBoxNeighborhood->SelectedIndex = 0;

	return System::Void();
}

System::Void GDMwGB::MyForm::Close(System::Object ^ sender, System::Windows::Forms::FormClosingEventArgs ^ e)
{
	System::Windows::Forms::DialogResult dr;
	dr = MessageBox::Show("Czy chcesz wyjœæ z aplikacji?", "GDMwGB", System::Windows::Forms::MessageBoxButtons::YesNo);
	if (dr == System::Windows::Forms::DialogResult::No)
	{
		e->Cancel = true;
	}
}

System::Void GDMwGB::MyForm::ViewChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (this->comboBoxView->SelectedIndex == 0) shaderIndex = 0;
	else if (this->comboBoxView->SelectedIndex == 1) shaderIndex = 1;
	else if (this->comboBoxView->SelectedIndex == 2) shaderIndex = 2;
	return System::Void();
}

System::Void GDMwGB::MyForm::comboBoxNucleation_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	this->dataGridView1->Rows->Add("Iloœæ", "5");
	return System::Void();
}

System::Void GDMwGB::MyForm::nucleationButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int c = 0;
	int::TryParse(this->dataGridView1->Rows[0]->Cells[1]->Value->ToString(), c);
	NucleonGenerator::random(this->simulation->cellularautomata,c);
	return System::Void();
}

System::Void GDMwGB::MyForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	MyNewForm form;
	form.ShowDialog();
	return System::Void();
}

System::Void GDMwGB::MyForm::MainForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	// no smaller than design time size

	this->MinimumSize = System::Drawing::Size(640, 480);

	// no larger than screen size
	this->MaximumSize = System::Drawing::Size(Screen::PrimaryScreen->Bounds.Width, Screen::PrimaryScreen->Bounds.Width);
		//System::Drawing::Size(Screen::PrimaryScreen::Bounds::Width, Screen.PrimaryScreen.Bounds.Height, (int)System.Windows.SystemParameters.PrimaryScreenHeight);
	this->colorFactory->generate(300*300*300);
	return System::Void();
}