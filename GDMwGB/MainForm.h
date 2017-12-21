#pragma once
 
#include "Camera.h"
#include "Mouse.h"
#include "Simulation.h"
#include "Calculations.h"
#include "ColorFactory.h"
#include "CellularAutomata.h"

#include "GrainBoundarySimulation.h"
#include "GrainGrowthSimulation.h"

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

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

namespace GDMwGB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
    
			srand(time(NULL));

			this->camera = new Camera();
			this->mouse = new Mouse();
			this->colorFactory = new ColorFactory();

			this->simulation = new GrainGrowthSimulation();

			this->oldWindowSize = this->Size;

			c = gcnew Calculations();
			c->simulation = this->simulation;

			this->shaderProgram = new int[3];
			this->projection = new glm::mat4();
			this->view = new glm::mat4();
			this->model = new glm::mat4();

			this->VAO = new unsigned int;
			this->VBO = new unsigned int;
			this->EBO = new unsigned int;
			this->colorVBO = new unsigned int;
			this->translationsVBO = new unsigned int;

			this->comboBoxNeighborhood->SelectedIndex = 0;
			this->comboBoxSymulation->SelectedIndex = 0;
			this->comboBoxView->SelectedIndex = 0;
			this->comboBoxNucleation->SelectedIndex = 0;
			this->CheckForIllegalCrossThreadCalls = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	//
	
	/*OpenGL*/
	unsigned int *VBO, *VAO, *EBO, *colorVBO, *translationsVBO;
	int * shaderProgram;
	int shaderIndex;

	glm::mat4	*projection,
				*model,
				*view;

	GLuint		modelLoc,
				viewLoc,
				projLoc,
				lightPosLoc;

	glm::vec3 * colors;
	glm::vec3 * translations;
	/* ****	*/
	//Kamera
	private: Camera * camera;
	//Mysz
	private: Mouse * mouse;
	//
	private: ColorFactory * colorFactory;
	//Kontrolka OpenGL

	//Kontrola MainWindow
	private: System::Drawing::Size oldWindowSize;
	private: System::Threading::Thread ^ calculationThread;
	//
	private: Calculations ^ c;
	//
	private: Simulation* simulation;
	private: System::Threading::Thread^ thread;
	private: System::Windows::Forms::Button^  simulateButton;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  plikToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  noweToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  wyjdzToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  comboBoxNeighborhood;

	private: System::Windows::Forms::ComboBox^  comboBoxSymulation;


	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  nucleationButton;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBoxNucleation;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::ComboBox^  comboBoxView;

	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Parametr;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Button^  button1;
	private: Zolver::OpenGLControl^  openGLControl1;

















		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->simulateButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->plikToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->noweToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->wyjdzToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxNeighborhood = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxSymulation = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Parametr = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nucleationButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBoxNucleation = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBoxView = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openGLControl1 = (gcnew Zolver::OpenGLControl());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// simulateButton
			// 
			this->simulateButton->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaption;
			this->simulateButton->Location = System::Drawing::Point(13, 525);
			this->simulateButton->Name = L"simulateButton";
			this->simulateButton->Size = System::Drawing::Size(75, 23);
			this->simulateButton->TabIndex = 1;
			this->simulateButton->Text = L"Start";
			this->simulateButton->UseVisualStyleBackColor = true;
			this->simulateButton->Click += gcnew System::EventHandler(this, &MyForm::Simulate_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->plikToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(784, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"MyFormMenuStrip";
			// 
			// plikToolStripMenuItem
			// 
			this->plikToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->noweToolStripMenuItem,
					this->wyjdzToolStripMenuItem
			});
			this->plikToolStripMenuItem->Name = L"plikToolStripMenuItem";
			this->plikToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->plikToolStripMenuItem->Text = L"Plik";
			// 
			// noweToolStripMenuItem
			// 
			this->noweToolStripMenuItem->Name = L"noweToolStripMenuItem";
			this->noweToolStripMenuItem->Size = System::Drawing::Size(106, 22);
			this->noweToolStripMenuItem->Text = L"Nowe";
			this->noweToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::NewMenuButton);
			// 
			// wyjdzToolStripMenuItem
			// 
			this->wyjdzToolStripMenuItem->Name = L"wyjdzToolStripMenuItem";
			this->wyjdzToolStripMenuItem->Size = System::Drawing::Size(106, 22);
			this->wyjdzToolStripMenuItem->Text = L"Wyjdz";
			this->wyjdzToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ExitMenuButton);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->comboBoxNeighborhood);
			this->groupBox1->Location = System::Drawing::Point(12, 88);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(229, 53);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Grain Growth";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(61, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"S¹siedztwo";
			// 
			// comboBoxNeighborhood
			// 
			this->comboBoxNeighborhood->FormattingEnabled = true;
			this->comboBoxNeighborhood->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Moore", L"Von Neumann", L"Pentagonal",
					L"Hexagonal"
			});
			this->comboBoxNeighborhood->Location = System::Drawing::Point(108, 19);
			this->comboBoxNeighborhood->Name = L"comboBoxNeighborhood";
			this->comboBoxNeighborhood->Size = System::Drawing::Size(120, 21);
			this->comboBoxNeighborhood->TabIndex = 0;
			this->comboBoxNeighborhood->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::NeighborhoodChanged);
			// 
			// comboBoxSymulation
			// 
			this->comboBoxSymulation->FormattingEnabled = true;
			this->comboBoxSymulation->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Grain Growth", L"Grain Growth ( GB )" });
			this->comboBoxSymulation->Location = System::Drawing::Point(107, 19);
			this->comboBoxSymulation->Name = L"comboBoxSymulation";
			this->comboBoxSymulation->Size = System::Drawing::Size(122, 21);
			this->comboBoxSymulation->TabIndex = 4;
			this->comboBoxSymulation->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::SimulationChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->dataGridView1);
			this->groupBox2->Controls->Add(this->nucleationButton);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->comboBoxNucleation);
			this->groupBox2->Location = System::Drawing::Point(13, 147);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(228, 151);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Grain Nucleation";
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->Parametr,
					this->Column1
			});
			this->dataGridView1->GridColor = System::Drawing::SystemColors::AppWorkspace;
			this->dataGridView1->Location = System::Drawing::Point(8, 75);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 4;
			this->dataGridView1->Size = System::Drawing::Size(219, 70);
			this->dataGridView1->TabIndex = 3;
			// 
			// Parametr
			// 
			this->Parametr->HeaderText = L"Parametr";
			this->Parametr->Name = L"Parametr";
			this->Parametr->ReadOnly = true;
			this->Parametr->Width = 108;
			// 
			// Column1
			// 
			this->Column1->FillWeight = 120;
			this->Column1->HeaderText = L"Wartoœæ";
			this->Column1->Name = L"Column1";
			this->Column1->Resizable = System::Windows::Forms::DataGridViewTriState::True;
			this->Column1->Width = 108;
			// 
			// nucleationButton
			// 
			this->nucleationButton->Location = System::Drawing::Point(147, 19);
			this->nucleationButton->Name = L"nucleationButton";
			this->nucleationButton->Size = System::Drawing::Size(81, 23);
			this->nucleationButton->TabIndex = 2;
			this->nucleationButton->Text = L"Generuj";
			this->nucleationButton->UseVisualStyleBackColor = true;
			this->nucleationButton->Click += gcnew System::EventHandler(this, &MyForm::nucleationButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 13);
			this->label3->TabIndex = 1;
			this->label3->Text = L"Rodzaj";
			// 
			// comboBoxNucleation
			// 
			this->comboBoxNucleation->FormattingEnabled = true;
			this->comboBoxNucleation->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Random" });
			this->comboBoxNucleation->Location = System::Drawing::Point(107, 48);
			this->comboBoxNucleation->Name = L"comboBoxNucleation";
			this->comboBoxNucleation->Size = System::Drawing::Size(121, 21);
			this->comboBoxNucleation->TabIndex = 0;
			this->comboBoxNucleation->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxNucleation_SelectedIndexChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->comboBoxSymulation);
			this->groupBox3->Location = System::Drawing::Point(12, 29);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(235, 53);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Symulacja";
			// 
			// comboBoxView
			// 
			this->comboBoxView->FormattingEnabled = true;
			this->comboBoxView->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Normal", L"NoOneGrain", L"NoGrainBoundary" });
			this->comboBoxView->Location = System::Drawing::Point(101, 19);
			this->comboBoxView->Name = L"comboBoxView";
			this->comboBoxView->Size = System::Drawing::Size(91, 21);
			this->comboBoxView->TabIndex = 7;
			this->comboBoxView->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::ViewChanged);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->comboBoxView);
			this->groupBox4->Location = System::Drawing::Point(22, 304);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(218, 54);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Widok";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Location = System::Drawing::Point(12, 365);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(228, 154);
			this->flowLayoutPanel1->TabIndex = 9;
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaption;
			this->button1->Location = System::Drawing::Point(166, 525);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 10;
			this->button1->Text = L"NewForm";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// openGLControl1
			// 
			this->openGLControl1->AutomaticSwapBuffer = true;
			this->openGLControl1->AverageFrameRateBase = 1;
			this->openGLControl1->Location = System::Drawing::Point(252, 12);
			this->openGLControl1->MaxFrameRate = 60;
			this->openGLControl1->Name = L"openGLControl1";
			this->openGLControl1->PreciseTiming = false;
			this->openGLControl1->RenderStyle = Zolver::ERenderStyle::Auto;
			this->openGLControl1->ShowFrameRate = false;
			this->openGLControl1->Size = System::Drawing::Size(520, 520);
			this->openGLControl1->TabIndex = 11;
			this->openGLControl1->Text = L"openGLControl1";
			this->openGLControl1->OpenGLMouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseWheel);
			this->openGLControl1->OpenGLMouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseUp);
			this->openGLControl1->OpenGLMouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseMove);
			this->openGLControl1->OpenGLMouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseDown);
			this->openGLControl1->OpenGLResize += gcnew System::EventHandler(this, &MyForm::OpenGLResize);
			this->openGLControl1->OpenGLRender += gcnew System::EventHandler(this, &MyForm::OpenGLRender);
			this->openGLControl1->OpenGLInit += gcnew System::EventHandler(this, &MyForm::OpenGLInit);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->openGLControl1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->simulateButton);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"GDMwGB";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::Close);
			this->Load += gcnew System::EventHandler(this, &MyForm::MainForm_Load);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MainForm_Resize);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//OpenGL context
	private:
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	System::Void OpenGLInit(System::Object^  sender, System::EventArgs^  e);
	private: System::Void OpenGLRender(System::Object^  sender, System::EventArgs^  e);
	private: System::Void OpenGLResize(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	//Main window
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Simulate_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void NewMenuButton(System::Object^  sender, System::EventArgs^  e);
	private: System::Void ExitMenuButton(System::Object^  sender, System::EventArgs^  e);
	private: System::Void NeighborhoodChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SimulationChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void Close(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void ViewChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void comboBoxNucleation_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void nucleationButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
};
}
