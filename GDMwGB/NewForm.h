#pragma once

namespace GDMwGB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NewForm
	/// </summary>
	public ref class NewForm : public System::Windows::Forms::Form
	{
	public:
		NewForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//this->XTextBox->V
			Done = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NewForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public:
		Boolean Done;
		int x;
		int y;
		int z;

	private: System::Windows::Forms::Button^  OkButton;
	public:
	private: System::Windows::Forms::Button^  AnulujButton;
	private: System::Windows::Forms::Label^  label1;




	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	public: System::Windows::Forms::NumericUpDown^  XNumericUpDown;
	public: System::Windows::Forms::NumericUpDown^  YNumericUpDown;
	public: System::Windows::Forms::NumericUpDown^  ZNumericUpDown;
	private:





	private:
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
			this->OkButton = (gcnew System::Windows::Forms::Button());
			this->AnulujButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->XNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->YNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->ZNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ZNumericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// OkButton
			// 
			this->OkButton->Location = System::Drawing::Point(40, 87);
			this->OkButton->Name = L"OkButton";
			this->OkButton->Size = System::Drawing::Size(75, 23);
			this->OkButton->TabIndex = 0;
			this->OkButton->Text = L"Ok";
			this->OkButton->UseVisualStyleBackColor = true;
			this->OkButton->Click += gcnew System::EventHandler(this, &NewForm::OkButtonClick);
			// 
			// AnulujButton
			// 
			this->AnulujButton->Location = System::Drawing::Point(140, 87);
			this->AnulujButton->Name = L"AnulujButton";
			this->AnulujButton->Size = System::Drawing::Size(75, 23);
			this->AnulujButton->TabIndex = 1;
			this->AnulujButton->Text = L"Anuluj";
			this->AnulujButton->UseVisualStyleBackColor = true;
			this->AnulujButton->Click += gcnew System::EventHandler(this, &NewForm::CancelButtonClick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(66, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(14, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"X";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(66, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(14, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Y";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(66, 61);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(14, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Z";
			// 
			// XNumericUpDown
			// 
			this->XNumericUpDown->Location = System::Drawing::Point(155, 7);
			this->XNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->XNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->XNumericUpDown->Name = L"XNumericUpDown";
			this->XNumericUpDown->Size = System::Drawing::Size(40, 20);
			this->XNumericUpDown->TabIndex = 7;
			this->XNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// YNumericUpDown
			// 
			this->YNumericUpDown->Location = System::Drawing::Point(155, 33);
			this->YNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->YNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->YNumericUpDown->Name = L"YNumericUpDown";
			this->YNumericUpDown->Size = System::Drawing::Size(40, 20);
			this->YNumericUpDown->TabIndex = 8;
			this->YNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// ZNumericUpDown
			// 
			this->ZNumericUpDown->Location = System::Drawing::Point(155, 59);
			this->ZNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->ZNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ZNumericUpDown->Name = L"ZNumericUpDown";
			this->ZNumericUpDown->Size = System::Drawing::Size(40, 20);
			this->ZNumericUpDown->TabIndex = 9;
			this->ZNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// NewForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(244, 118);
			this->Controls->Add(this->ZNumericUpDown);
			this->Controls->Add(this->YNumericUpDown);
			this->Controls->Add(this->XNumericUpDown);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->AnulujButton);
			this->Controls->Add(this->OkButton);
			this->Name = L"NewForm";
			this->Text = L"New";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->XNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->YNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ZNumericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void OkButtonClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void CancelButtonClick(System::Object^  sender, System::EventArgs^  e);
};
}
