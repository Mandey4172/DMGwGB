#pragma once

#include"Camera.h"
#include"Mouse.h"
#include"Simulation.h"

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 

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

			this->simulation = new Simulation();
			this->oldWindowSize = this->Size;
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
	//Kamera
	private: Camera * camera;
	//Mysz
	private: Mouse * mouse;
	//Kontrolka OpenGL
	private: Zolver::OpenGLControl^  openGLControl1;
	//Kontrola MainWindow
	private: System::Drawing::Size oldWindowSize;
			 
	//
	private: Simulation* simulation;
	private:System::Threading::Thread^ thread;
	private: System::Windows::Forms::Button^  Simulate;

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
			this->openGLControl1 = (gcnew Zolver::OpenGLControl());
			this->Simulate = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openGLControl1
			// 
			this->openGLControl1->AutomaticSwapBuffer = true;
			this->openGLControl1->AverageFrameRateBase = 1;
			this->openGLControl1->Location = System::Drawing::Point(242, 19);
			this->openGLControl1->MaxFrameRate = 60;
			this->openGLControl1->Name = L"openGLControl1";
			this->openGLControl1->PreciseTiming = false;
			this->openGLControl1->RenderStyle = Zolver::ERenderStyle::Auto;
			this->openGLControl1->ShowFrameRate = false;
			this->openGLControl1->Size = System::Drawing::Size(530, 530);
			this->openGLControl1->TabIndex = 0;
			this->openGLControl1->Text = L"openGLControl1";
			this->openGLControl1->OpenGLMouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseWheel);
			this->openGLControl1->OpenGLMouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseUp);
			this->openGLControl1->OpenGLMouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseMove);
			this->openGLControl1->OpenGLMouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseDown);
			this->openGLControl1->OpenGLResize += gcnew System::EventHandler(this, &MyForm::OpenGLResize);
			this->openGLControl1->OpenGLRender += gcnew System::EventHandler(this, &MyForm::OpenGLRender);
			this->openGLControl1->OpenGLInit += gcnew System::EventHandler(this, &MyForm::OpenGLInit);
			// 
			// Simulate
			// 
			this->Simulate->Location = System::Drawing::Point(13, 525);
			this->Simulate->Name = L"Simulate";
			this->Simulate->Size = System::Drawing::Size(75, 23);
			this->Simulate->TabIndex = 1;
			this->Simulate->Text = L"Step";
			this->Simulate->UseVisualStyleBackColor = true;
			this->Simulate->Click += gcnew System::EventHandler(this, &MyForm::Simulate_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->Simulate);
			this->Controls->Add(this->openGLControl1);
			this->Name = L"MyForm";
			this->Text = L"GDMwGB";
			this->Load += gcnew System::EventHandler(this, &MyForm::MainForm_Load);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MainForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	//OpenGL context
	private: System::Void OpenGLInit(System::Object^  sender, System::EventArgs^  e);
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
};
}
