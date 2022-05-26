#pragma once

#include <vector>
#include "Shape.h"
#include "Group.h"
#include "Rectangle.h"
#include "Circle.h"

namespace GroupEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ infoLabel;
	private: System::Windows::Forms::TextBox^ commandTextBox;


	private: Group* mainGroup = new Group(0, 0, 500, 500);
	private: System::Windows::Forms::PictureBox^ canvas;


	private:
		
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->infoLabel = (gcnew System::Windows::Forms::Label());
			this->commandTextBox = (gcnew System::Windows::Forms::TextBox());
			this->canvas = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->BeginInit();
			this->SuspendLayout();
			// 
			// infoLabel
			// 
			this->infoLabel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->infoLabel->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->infoLabel->Location = System::Drawing::Point(565, 12);
			this->infoLabel->Name = L"infoLabel";
			this->infoLabel->Size = System::Drawing::Size(371, 443);
			this->infoLabel->TabIndex = 0;
			// 
			// commandTextBox
			// 
			this->commandTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->commandTextBox->Location = System::Drawing::Point(565, 484);
			this->commandTextBox->Name = L"commandTextBox";
			this->commandTextBox->Size = System::Drawing::Size(371, 29);
			this->commandTextBox->TabIndex = 1;
			this->commandTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::commandTextBox_KeyPress);
			// 
			// canvas
			// 
			this->canvas->Location = System::Drawing::Point(12, 12);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(502, 502);
			this->canvas->TabIndex = 3;
			this->canvas->TabStop = false;
			this->canvas->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::canvas_Paint);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(973, 525);
			this->Controls->Add(this->canvas);
			this->Controls->Add(this->commandTextBox);
			this->Controls->Add(this->infoLabel);
			this->Name = L"MainForm";
			this->Text = L"GroupEditor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void commandTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	private: System::Void canvas_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
};
}
