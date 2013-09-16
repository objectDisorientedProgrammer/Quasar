#pragma once
#include "MainWindow.h"

namespace Quasar {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Splash
	/// </summary>
	public ref class Splash : public System::Windows::Forms::Form
	{
	public:
		Splash(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Splash()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  tmrLoadMain;
	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Splash::typeid));
			this->tmrLoadMain = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tmrLoadMain
			// 
			this->tmrLoadMain->Enabled = true;
			this->tmrLoadMain->Interval = 2000;
			this->tmrLoadMain->Tick += gcnew System::EventHandler(this, &Splash::tmrLoadMain_Tick);
			// 
			// Splash
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(798, 407);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Splash";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &Splash::Splash_Load);
			this->Click += gcnew System::EventHandler(this, &Splash::Splash_Click);
			this->DoubleClick += gcnew System::EventHandler(this, &Splash::Splash_DoubleClick);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Splash_Load(System::Object^  sender, System::EventArgs^  e) {

			 }
#if 1
	private: System::Void tmrLoadMain_Tick(System::Object^  sender, System::EventArgs^  e) {
				 tmrLoadMain->Enabled = false;
				 Quasar::MainWindow mainForm;
				 this->Hide();
				 mainForm.ShowDialog();
			 }
#endif

#if 0
	private: System::Void tmrLoadMain_Tick(System::Object^  sender, System::EventArgs^  e) {
				 tmrLoadMain->Enabled = false;
				 this->Close();
			 }
#endif
	private: System::Void Splash_Click(System::Object^  sender, System::EventArgs^  e) {
				 tmrLoadMain->Enabled = false;
			 }
	private: System::Void Splash_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
				 tmrLoadMain->Enabled = true;
			 }
	};
}
