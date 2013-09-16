/*----------------------------------------------------------------------
   
	Filename:  MainWindow.h

	Author: James Howard

	Description:
 	The UI WindowsForm for running a search on the Quasar database.

----------------------------------------------------------------------*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#pragma once

#include "NodeManager.h"
#include "Node.h"
#include "DocumentData.h"
#include "WebsiteData.h"
#include "PictureData.h"
#include "ContactData.h"
#include "SearchManager.h"
#include "string.h"
#include "MarshalString.h"
#include <vector>
#include <set>
#include <iostream>
#using <mscorlib.dll>
#using <System.dll>
#include <exception>

namespace Quasar {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{

	private:
	NodeManager *nm;
	Node *activeNode;
	vector<Node*> *results;
	void resetActiveNode() {activeNode = NULL;}
	int getCategoryIndex(){
		for(int i=0; i<cbCategories->Items->Count; i++)
			if(cbCategories->Text==cbCategories->Items[i]->ToString()) return i;
		return 0;
	}

	// Fills the active node's fields
	void fillActiveNode()
	{
			string std_value = "";
			DocumentData *docData;
			WebsiteData *webData;
			PictureData *picData;
			ContactData *conData;

			MarshalString(txtNodeTitle->Text, std_value);
			activeNode->setTitle(std_value);
			MarshalString(txtNodeDescrip->Text, std_value);
			activeNode->setDescription(std_value);
			MarshalString(txtNodeDate->Text, std_value);
			activeNode->setDate(std_value);
			MarshalString(txtNodeKeywords->Text, std_value);
			activeNode->setKeywords(std_value);

			if(txtDocPath->Text != "") {
				MarshalString(txtDocPath->Text, std_value);
				if(activeNode->document)
					activeNode->document->setPath(std_value);
				else{
					docData = new DocumentData(std_value);
					activeNode->document = docData;
				}
			}

			if(txtWebURL->Text != ""){
				MarshalString(txtWebURL->Text, std_value);
				if(activeNode->website)
					activeNode->website->setSiteURL(std_value);
				else{
					webData = new WebsiteData(std_value);
					activeNode->website = webData;
				}
			}

			if(txtPicturePath->Text != ""){
				MarshalString(txtPicturePath->Text, std_value);
				if(activeNode->picture)
					activeNode->picture->setPath(std_value);
				else{
					picData = new PictureData(std_value);
					activeNode->picture = picData;
				}
			}

			if(    txtContactFirstName->Text != "" || txtContactLastName->Text != ""
			    || txtContactPhoneNum->Text != "" || txtContactEmail->Text != "" ){
				if(activeNode->contact){
					MarshalString(txtContactFirstName->Text, std_value);
					activeNode->contact->setFirstName(std_value);
					MarshalString(txtContactLastName->Text, std_value);
					activeNode->contact->setLastName(std_value);
					MarshalString(txtContactPhoneNum->Text, std_value);
					activeNode->contact->setPhoneNumber(std_value);
					MarshalString(txtContactEmail->Text, std_value);
					activeNode->contact->setEmail(std_value);
				} else {
					conData = new ContactData;
					MarshalString(txtContactFirstName->Text, std_value);
					conData->setFirstName(std_value);
					MarshalString(txtContactLastName->Text, std_value);
					conData->setLastName(std_value);
					MarshalString(txtContactPhoneNum->Text, std_value);
					conData->setPhoneNumber(std_value);
					MarshalString(txtContactEmail->Text, std_value);
					conData->setEmail(std_value);
					activeNode->contact = conData;
				}
			}
	}

	// Adds the active node to the list and updates the GUI
	void addActiveNode()
	{
		nm->_addNode(activeNode);
		updateNodeCountLabel(nm->getTotalNodeCount());
		resetActiveNode();
		resetNodeFields();
	}

	private: System::Windows::Forms::Button^  btnNewEntry;
	private: System::Windows::Forms::Button^  btnResetEntry;
	private: System::Windows::Forms::Button^  btnSaveEntry;
	private: System::Windows::Forms::Button^  btnSetDate;
	private: System::Windows::Forms::DateTimePicker^  datePicker;
	private: System::Windows::Forms::Label^  lblKeywords;
	private: System::Windows::Forms::Button^  btnDeleteEntry;
	
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			nm = new NodeManager("Quasar.dat");
			results = new vector<Node*>;
			activeNode = NULL;
			// Hide Modify Node Section of Main Window
			btnModifyToggle->Text = ">>";
			this->Width = gbNode->Left + 6;
			this->Width = gbNode->Left + 6;

			reloadListBox();	// fill the listbox at start
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Label^  lblCategories;
	private: System::Windows::Forms::TextBox^  txtSearch;
	private: System::Windows::Forms::Label^  lblSearch;
	private: System::Windows::Forms::Button^  btnSearch;
	private: System::Windows::Forms::GroupBox^  gbResults;
	private: System::Windows::Forms::GroupBox^  gbFeatures;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnResearch;
	private: System::Windows::Forms::ListBox^  lstResults;
	private: System::Windows::Forms::ComboBox^  cbCategories;
	private: System::Windows::Forms::GroupBox^  gbNode;
	private: System::Windows::Forms::TextBox^  txtNodeKeywords;
	private: System::Windows::Forms::Label^  lblNodeDate;
	private: System::Windows::Forms::Label^  lblNodeDescip;
	private: System::Windows::Forms::Label^  lblNodeTitle;
	private: System::Windows::Forms::TextBox^  txtNodeDate;
	private: System::Windows::Forms::TextBox^  txtNodeDescrip;
	private: System::Windows::Forms::TextBox^  txtNodeTitle;
	private: System::Windows::Forms::Label^  lblAddEdit;
	private: System::Windows::Forms::GroupBox^  gbPicture;
	private: System::Windows::Forms::Label^  lblPath;
	private: System::Windows::Forms::TextBox^  txtPicturePath;
	private: System::Windows::Forms::GroupBox^  gbContact;
	private: System::Windows::Forms::Button^  btnModifyToggle;
	private: System::Windows::Forms::Label^  lblContactEmail;
	private: System::Windows::Forms::Label^  lblContactPhoneNum;
	private: System::Windows::Forms::Label^  lblContactLastName;
	private: System::Windows::Forms::Label^  lblContactFirstName;
	private: System::Windows::Forms::TextBox^  txtContactEmail;
	private: System::Windows::Forms::TextBox^  txtContactPhoneNum;
	private: System::Windows::Forms::TextBox^  txtContactLastName;
	private: System::Windows::Forms::TextBox^  txtContactFirstName;
	private: System::Windows::Forms::GroupBox^  gbWebsite;
	private: System::Windows::Forms::Label^  lblWebURL;
	private: System::Windows::Forms::TextBox^  txtWebURL;
	private: System::Windows::Forms::GroupBox^  gbDocument;
	private: System::Windows::Forms::Label^  lblDocPath;
	private: System::Windows::Forms::TextBox^  txtDocPath;
	private: System::Windows::Forms::Label^  lblResultCount;
	private: System::Windows::Forms::GroupBox^  gbNodeInfo;
	private: System::Windows::Forms::Label^  lblNodeCount;
	private: System::Windows::Forms::Button^  btnExit;
	private: System::Windows::Forms::Button^  btnShowAll;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		void updateNodeCountLabel(int total){
			String^ txtTotal = "Total: ";
			txtTotal += total.ToString();
			lblNodeCount->Text = txtTotal;
		}

		void updateResultCountLabel(int numResults){
			String^ txtNumResults = "Results: ";
			txtNumResults += numResults.ToString();
			lblResultCount->Text = txtNumResults;
		}

		void resetNodeFields(){
			txtNodeTitle->Text = "";
			txtNodeDescrip->Text = "";
			txtNodeDate->Text = "";
			txtNodeKeywords->Text = "";
			txtDocPath->Text = "";
			txtWebURL->Text = "";
			txtPicturePath->Text = "";
			txtContactFirstName->Text = "";
			txtContactLastName->Text = "";
			txtContactPhoneNum->Text = "";
			txtContactEmail->Text = "";
		}

		void setNodeFields(){
			String^ sys_value;
			resetNodeFields();
			if(activeNode){
				sys_value = gcnew String(activeNode->getTitle().c_str());
				txtNodeTitle->Text = sys_value;
				sys_value = gcnew String(activeNode->getDescription().c_str());
				txtNodeDescrip->Text = sys_value;
				sys_value = gcnew String(activeNode->getDate().c_str());
				txtNodeDate->Text = sys_value;
				sys_value = gcnew String(activeNode->getKeywords().c_str());
				txtNodeKeywords->Text = sys_value;

				if(activeNode->document){
					sys_value = gcnew String(activeNode->document->getPath().c_str());
					txtDocPath->Text = sys_value;
				}

				if(activeNode->website){
					sys_value = gcnew String(activeNode->website->getSiteURL().c_str());
					txtWebURL->Text = sys_value;
				}

				if(activeNode->picture){
					sys_value = gcnew String(activeNode->picture->getPath().c_str());
					txtPicturePath->Text = sys_value;
				}

				if(activeNode->contact){
					sys_value = gcnew String(activeNode->contact->getFirstName().c_str());
					txtContactFirstName->Text = sys_value;
					sys_value = gcnew String(activeNode->contact->getLastName().c_str());
					txtContactLastName->Text = sys_value;
					sys_value = gcnew String(activeNode->contact->getPhoneNumber().c_str());
					txtContactPhoneNum->Text = sys_value;
					sys_value = gcnew String(activeNode->contact->getEmail().c_str());
					txtContactEmail->Text = sys_value;
				}
			}
		}
		// Populate the listBox
		void showResults(){
			string stdTitle;
			String^ sysTitle;
			lstResults->Items->Clear();
			if(!results->size()) return;
			for(vector<Node*>::iterator iter=results->begin(); iter!=results->end(); iter++){
				stdTitle = (*iter)->getTitle();
				sysTitle =	gcnew String(stdTitle.c_str());;
				lstResults->Items->Add(sysTitle);
			}
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->lblCategories = (gcnew System::Windows::Forms::Label());
			this->txtSearch = (gcnew System::Windows::Forms::TextBox());
			this->lblSearch = (gcnew System::Windows::Forms::Label());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->gbResults = (gcnew System::Windows::Forms::GroupBox());
			this->lstResults = (gcnew System::Windows::Forms::ListBox());
			this->gbFeatures = (gcnew System::Windows::Forms::GroupBox());
			this->btnShowAll = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnResearch = (gcnew System::Windows::Forms::Button());
			this->cbCategories = (gcnew System::Windows::Forms::ComboBox());
			this->gbNode = (gcnew System::Windows::Forms::GroupBox());
			this->lblKeywords = (gcnew System::Windows::Forms::Label());
			this->datePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->btnSetDate = (gcnew System::Windows::Forms::Button());
			this->txtNodeKeywords = (gcnew System::Windows::Forms::TextBox());
			this->lblNodeDate = (gcnew System::Windows::Forms::Label());
			this->lblNodeDescip = (gcnew System::Windows::Forms::Label());
			this->lblNodeTitle = (gcnew System::Windows::Forms::Label());
			this->txtNodeDate = (gcnew System::Windows::Forms::TextBox());
			this->txtNodeDescrip = (gcnew System::Windows::Forms::TextBox());
			this->txtNodeTitle = (gcnew System::Windows::Forms::TextBox());
			this->lblAddEdit = (gcnew System::Windows::Forms::Label());
			this->gbPicture = (gcnew System::Windows::Forms::GroupBox());
			this->lblPath = (gcnew System::Windows::Forms::Label());
			this->txtPicturePath = (gcnew System::Windows::Forms::TextBox());
			this->gbContact = (gcnew System::Windows::Forms::GroupBox());
			this->lblContactEmail = (gcnew System::Windows::Forms::Label());
			this->lblContactPhoneNum = (gcnew System::Windows::Forms::Label());
			this->lblContactLastName = (gcnew System::Windows::Forms::Label());
			this->lblContactFirstName = (gcnew System::Windows::Forms::Label());
			this->txtContactEmail = (gcnew System::Windows::Forms::TextBox());
			this->txtContactPhoneNum = (gcnew System::Windows::Forms::TextBox());
			this->txtContactLastName = (gcnew System::Windows::Forms::TextBox());
			this->txtContactFirstName = (gcnew System::Windows::Forms::TextBox());
			this->gbWebsite = (gcnew System::Windows::Forms::GroupBox());
			this->lblWebURL = (gcnew System::Windows::Forms::Label());
			this->txtWebURL = (gcnew System::Windows::Forms::TextBox());
			this->gbDocument = (gcnew System::Windows::Forms::GroupBox());
			this->lblDocPath = (gcnew System::Windows::Forms::Label());
			this->txtDocPath = (gcnew System::Windows::Forms::TextBox());
			this->lblResultCount = (gcnew System::Windows::Forms::Label());
			this->gbNodeInfo = (gcnew System::Windows::Forms::GroupBox());
			this->lblNodeCount = (gcnew System::Windows::Forms::Label());
			this->btnModifyToggle = (gcnew System::Windows::Forms::Button());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->btnNewEntry = (gcnew System::Windows::Forms::Button());
			this->btnResetEntry = (gcnew System::Windows::Forms::Button());
			this->btnSaveEntry = (gcnew System::Windows::Forms::Button());
			this->btnDeleteEntry = (gcnew System::Windows::Forms::Button());
			this->gbResults->SuspendLayout();
			this->gbFeatures->SuspendLayout();
			this->gbNode->SuspendLayout();
			this->gbPicture->SuspendLayout();
			this->gbContact->SuspendLayout();
			this->gbWebsite->SuspendLayout();
			this->gbDocument->SuspendLayout();
			this->gbNodeInfo->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblCategories
			// 
			this->lblCategories->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblCategories->Location = System::Drawing::Point(300, 59);
			this->lblCategories->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblCategories->Name = L"lblCategories";
			this->lblCategories->Size = System::Drawing::Size(204, 15);
			this->lblCategories->TabIndex = 1;
			this->lblCategories->Text = L"Limit results by specifying a category";
			// 
			// txtSearch
			// 
			this->txtSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtSearch->Location = System::Drawing::Point(104, 14);
			this->txtSearch->Margin = System::Windows::Forms::Padding(4);
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->Size = System::Drawing::Size(421, 32);
			this->txtSearch->TabIndex = 0;
			this->txtSearch->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::txtSearch_KeyPress);
			// 
			// lblSearch
			// 
			this->lblSearch->AutoSize = true;
			this->lblSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblSearch->Location = System::Drawing::Point(5, 14);
			this->lblSearch->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblSearch->Name = L"lblSearch";
			this->lblSearch->Size = System::Drawing::Size(91, 29);
			this->lblSearch->TabIndex = 3;
			this->lblSearch->Text = L"Quasar";
			// 
			// btnSearch
			// 
			this->btnSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnSearch->Location = System::Drawing::Point(535, 14);
			this->btnSearch->Margin = System::Windows::Forms::Padding(4);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(109, 33);
			this->btnSearch->TabIndex = 1;
			this->btnSearch->Text = L"Search";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &MainWindow::btnSearch_Click);
			// 
			// gbResults
			// 
			this->gbResults->Controls->Add(this->lstResults);
			this->gbResults->Location = System::Drawing::Point(10, 90);
			this->gbResults->Margin = System::Windows::Forms::Padding(4);
			this->gbResults->Name = L"gbResults";
			this->gbResults->Padding = System::Windows::Forms::Padding(4);
			this->gbResults->Size = System::Drawing::Size(577, 457);
			this->gbResults->TabIndex = 3;
			this->gbResults->TabStop = false;
			this->gbResults->Text = L"Entries";
			// 
			// lstResults
			// 
			this->lstResults->FormattingEnabled = true;
			this->lstResults->Location = System::Drawing::Point(9, 25);
			this->lstResults->Margin = System::Windows::Forms::Padding(4);
			this->lstResults->Name = L"lstResults";
			this->lstResults->Size = System::Drawing::Size(555, 420);
			this->lstResults->TabIndex = 4;
			this->lstResults->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::lstResults_SelectedIndexChanged);
			this->lstResults->DoubleClick += gcnew System::EventHandler(this, &MainWindow::lstResults_DoubleClick);
			this->lstResults->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainWindow::lstResults_MouseDoubleClick);
			// 
			// gbFeatures
			// 
			this->gbFeatures->Controls->Add(this->btnShowAll);
			this->gbFeatures->Controls->Add(this->btnSave);
			this->gbFeatures->Controls->Add(this->btnResearch);
			this->gbFeatures->Location = System::Drawing::Point(289, 551);
			this->gbFeatures->Margin = System::Windows::Forms::Padding(4);
			this->gbFeatures->Name = L"gbFeatures";
			this->gbFeatures->Padding = System::Windows::Forms::Padding(4);
			this->gbFeatures->Size = System::Drawing::Size(298, 75);
			this->gbFeatures->TabIndex = 6;
			this->gbFeatures->TabStop = false;
			this->gbFeatures->Text = L"Features";
			// 
			// btnShowAll
			// 
			this->btnShowAll->Location = System::Drawing::Point(210, 21);
			this->btnShowAll->Margin = System::Windows::Forms::Padding(4);
			this->btnShowAll->Name = L"btnShowAll";
			this->btnShowAll->Size = System::Drawing::Size(80, 33);
			this->btnShowAll->TabIndex = 9;
			this->btnShowAll->Text = L"Show All";
			this->btnShowAll->UseVisualStyleBackColor = true;
			this->btnShowAll->Click += gcnew System::EventHandler(this, &MainWindow::btnShowAll_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(117, 21);
			this->btnSave->Margin = System::Windows::Forms::Padding(4);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(85, 33);
			this->btnSave->TabIndex = 8;
			this->btnSave->Text = L"Save to File";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &MainWindow::btnSave_Click);
			// 
			// btnResearch
			// 
			this->btnResearch->Location = System::Drawing::Point(15, 21);
			this->btnResearch->Margin = System::Windows::Forms::Padding(4);
			this->btnResearch->Name = L"btnResearch";
			this->btnResearch->Size = System::Drawing::Size(94, 33);
			this->btnResearch->TabIndex = 7;
			this->btnResearch->Text = L"Research";
			this->btnResearch->UseVisualStyleBackColor = true;
			this->btnResearch->Click += gcnew System::EventHandler(this, &MainWindow::btnResearch_Click);
			// 
			// cbCategories
			// 
			this->cbCategories->FormattingEnabled = true;
			this->cbCategories->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"All Categories", L"Documents", L"Websites", 
				L"Pictures", L"Contacts"});
			this->cbCategories->Location = System::Drawing::Point(516, 57);
			this->cbCategories->Margin = System::Windows::Forms::Padding(4);
			this->cbCategories->Name = L"cbCategories";
			this->cbCategories->Size = System::Drawing::Size(128, 21);
			this->cbCategories->TabIndex = 2;
			this->cbCategories->Text = L"All Categories";
			this->cbCategories->TextUpdate += gcnew System::EventHandler(this, &MainWindow::cbCategories_TextUpdate);
			// 
			// gbNode
			// 
			this->gbNode->Controls->Add(this->lblKeywords);
			this->gbNode->Controls->Add(this->datePicker);
			this->gbNode->Controls->Add(this->btnSetDate);
			this->gbNode->Controls->Add(this->txtNodeKeywords);
			this->gbNode->Controls->Add(this->lblNodeDate);
			this->gbNode->Controls->Add(this->lblNodeDescip);
			this->gbNode->Controls->Add(this->lblNodeTitle);
			this->gbNode->Controls->Add(this->txtNodeDate);
			this->gbNode->Controls->Add(this->txtNodeDescrip);
			this->gbNode->Controls->Add(this->txtNodeTitle);
			this->gbNode->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gbNode->Location = System::Drawing::Point(669, 42);
			this->gbNode->Margin = System::Windows::Forms::Padding(4);
			this->gbNode->Name = L"gbNode";
			this->gbNode->Padding = System::Windows::Forms::Padding(4);
			this->gbNode->Size = System::Drawing::Size(613, 194);
			this->gbNode->TabIndex = 13;
			this->gbNode->TabStop = false;
			this->gbNode->Text = L"Properties";
			this->gbNode->Enter += gcnew System::EventHandler(this, &MainWindow::gbNode_Enter);
			// 
			// lblKeywords
			// 
			this->lblKeywords->AutoSize = true;
			this->lblKeywords->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblKeywords->Location = System::Drawing::Point(54, 143);
			this->lblKeywords->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblKeywords->Name = L"lblKeywords";
			this->lblKeywords->Size = System::Drawing::Size(73, 17);
			this->lblKeywords->TabIndex = 20;
			this->lblKeywords->Text = L"Keywords:";
			// 
			// datePicker
			// 
			this->datePicker->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->datePicker->Location = System::Drawing::Point(360, 100);
			this->datePicker->Name = L"datePicker";
			this->datePicker->Size = System::Drawing::Size(139, 26);
			this->datePicker->TabIndex = 17;
			// 
			// btnSetDate
			// 
			this->btnSetDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnSetDate->Location = System::Drawing::Point(505, 98);
			this->btnSetDate->Name = L"btnSetDate";
			this->btnSetDate->Size = System::Drawing::Size(83, 29);
			this->btnSetDate->TabIndex = 18;
			this->btnSetDate->Text = L"Set Date";
			this->btnSetDate->UseVisualStyleBackColor = true;
			this->btnSetDate->Click += gcnew System::EventHandler(this, &MainWindow::btnSetDate_Click);
			// 
			// txtNodeKeywords
			// 
			this->txtNodeKeywords->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtNodeKeywords->Location = System::Drawing::Point(147, 140);
			this->txtNodeKeywords->Margin = System::Windows::Forms::Padding(4);
			this->txtNodeKeywords->Name = L"txtNodeKeywords";
			this->txtNodeKeywords->Size = System::Drawing::Size(444, 23);
			this->txtNodeKeywords->TabIndex = 19;
			// 
			// lblNodeDate
			// 
			this->lblNodeDate->AutoSize = true;
			this->lblNodeDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblNodeDate->Location = System::Drawing::Point(85, 105);
			this->lblNodeDate->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblNodeDate->Name = L"lblNodeDate";
			this->lblNodeDate->Size = System::Drawing::Size(42, 17);
			this->lblNodeDate->TabIndex = 5;
			this->lblNodeDate->Text = L"Date:";
			// 
			// lblNodeDescip
			// 
			this->lblNodeDescip->AutoSize = true;
			this->lblNodeDescip->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblNodeDescip->Location = System::Drawing::Point(44, 69);
			this->lblNodeDescip->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblNodeDescip->Name = L"lblNodeDescip";
			this->lblNodeDescip->Size = System::Drawing::Size(83, 17);
			this->lblNodeDescip->TabIndex = 4;
			this->lblNodeDescip->Text = L"Description:";
			// 
			// lblNodeTitle
			// 
			this->lblNodeTitle->AutoSize = true;
			this->lblNodeTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblNodeTitle->Location = System::Drawing::Point(88, 34);
			this->lblNodeTitle->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblNodeTitle->Name = L"lblNodeTitle";
			this->lblNodeTitle->Size = System::Drawing::Size(39, 17);
			this->lblNodeTitle->TabIndex = 3;
			this->lblNodeTitle->Text = L"Title:";
			// 
			// txtNodeDate
			// 
			this->txtNodeDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtNodeDate->Location = System::Drawing::Point(147, 102);
			this->txtNodeDate->Margin = System::Windows::Forms::Padding(4);
			this->txtNodeDate->Name = L"txtNodeDate";
			this->txtNodeDate->Size = System::Drawing::Size(206, 23);
			this->txtNodeDate->TabIndex = 16;
			// 
			// txtNodeDescrip
			// 
			this->txtNodeDescrip->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtNodeDescrip->Location = System::Drawing::Point(147, 66);
			this->txtNodeDescrip->Margin = System::Windows::Forms::Padding(4);
			this->txtNodeDescrip->Name = L"txtNodeDescrip";
			this->txtNodeDescrip->Size = System::Drawing::Size(444, 23);
			this->txtNodeDescrip->TabIndex = 15;
			// 
			// txtNodeTitle
			// 
			this->txtNodeTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtNodeTitle->Location = System::Drawing::Point(147, 31);
			this->txtNodeTitle->Margin = System::Windows::Forms::Padding(4);
			this->txtNodeTitle->Name = L"txtNodeTitle";
			this->txtNodeTitle->Size = System::Drawing::Size(444, 23);
			this->txtNodeTitle->TabIndex = 14;
			// 
			// lblAddEdit
			// 
			this->lblAddEdit->AutoSize = true;
			this->lblAddEdit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblAddEdit->Location = System::Drawing::Point(665, 14);
			this->lblAddEdit->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblAddEdit->Name = L"lblAddEdit";
			this->lblAddEdit->Size = System::Drawing::Size(142, 20);
			this->lblAddEdit->TabIndex = 12;
			this->lblAddEdit->Text = L"Add or Edit Entries";
			// 
			// gbPicture
			// 
			this->gbPicture->Controls->Add(this->lblPath);
			this->gbPicture->Controls->Add(this->txtPicturePath);
			this->gbPicture->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gbPicture->Location = System::Drawing::Point(669, 354);
			this->gbPicture->Margin = System::Windows::Forms::Padding(4);
			this->gbPicture->Name = L"gbPicture";
			this->gbPicture->Padding = System::Windows::Forms::Padding(4);
			this->gbPicture->Size = System::Drawing::Size(299, 102);
			this->gbPicture->TabIndex = 24;
			this->gbPicture->TabStop = false;
			this->gbPicture->Text = L"Picture Properties";
			// 
			// lblPath
			// 
			this->lblPath->AutoSize = true;
			this->lblPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblPath->Location = System::Drawing::Point(25, 27);
			this->lblPath->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblPath->Name = L"lblPath";
			this->lblPath->Size = System::Drawing::Size(41, 17);
			this->lblPath->TabIndex = 13;
			this->lblPath->Text = L"Path:";
			// 
			// txtPicturePath
			// 
			this->txtPicturePath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtPicturePath->Location = System::Drawing::Point(29, 52);
			this->txtPicturePath->Margin = System::Windows::Forms::Padding(4);
			this->txtPicturePath->Name = L"txtPicturePath";
			this->txtPicturePath->Size = System::Drawing::Size(249, 23);
			this->txtPicturePath->TabIndex = 25;
			// 
			// gbContact
			// 
			this->gbContact->Controls->Add(this->lblContactEmail);
			this->gbContact->Controls->Add(this->lblContactPhoneNum);
			this->gbContact->Controls->Add(this->lblContactLastName);
			this->gbContact->Controls->Add(this->lblContactFirstName);
			this->gbContact->Controls->Add(this->txtContactEmail);
			this->gbContact->Controls->Add(this->txtContactPhoneNum);
			this->gbContact->Controls->Add(this->txtContactLastName);
			this->gbContact->Controls->Add(this->txtContactFirstName);
			this->gbContact->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gbContact->Location = System::Drawing::Point(669, 462);
			this->gbContact->Margin = System::Windows::Forms::Padding(4);
			this->gbContact->Name = L"gbContact";
			this->gbContact->Padding = System::Windows::Forms::Padding(4);
			this->gbContact->Size = System::Drawing::Size(613, 150);
			this->gbContact->TabIndex = 26;
			this->gbContact->TabStop = false;
			this->gbContact->Text = L"Contact Properties";
			// 
			// lblContactEmail
			// 
			this->lblContactEmail->AutoSize = true;
			this->lblContactEmail->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblContactEmail->Location = System::Drawing::Point(203, 84);
			this->lblContactEmail->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblContactEmail->Name = L"lblContactEmail";
			this->lblContactEmail->Size = System::Drawing::Size(46, 17);
			this->lblContactEmail->TabIndex = 10;
			this->lblContactEmail->Text = L"Email:";
			// 
			// lblContactPhoneNum
			// 
			this->lblContactPhoneNum->AutoSize = true;
			this->lblContactPhoneNum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblContactPhoneNum->Location = System::Drawing::Point(20, 84);
			this->lblContactPhoneNum->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblContactPhoneNum->Name = L"lblContactPhoneNum";
			this->lblContactPhoneNum->Size = System::Drawing::Size(107, 17);
			this->lblContactPhoneNum->TabIndex = 9;
			this->lblContactPhoneNum->Text = L"Phone Number:";
			// 
			// lblContactLastName
			// 
			this->lblContactLastName->AutoSize = true;
			this->lblContactLastName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblContactLastName->Location = System::Drawing::Point(203, 27);
			this->lblContactLastName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblContactLastName->Name = L"lblContactLastName";
			this->lblContactLastName->Size = System::Drawing::Size(80, 17);
			this->lblContactLastName->TabIndex = 8;
			this->lblContactLastName->Text = L"Last Name:";
			// 
			// lblContactFirstName
			// 
			this->lblContactFirstName->AutoSize = true;
			this->lblContactFirstName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblContactFirstName->Location = System::Drawing::Point(20, 27);
			this->lblContactFirstName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblContactFirstName->Name = L"lblContactFirstName";
			this->lblContactFirstName->Size = System::Drawing::Size(80, 17);
			this->lblContactFirstName->TabIndex = 6;
			this->lblContactFirstName->Text = L"First Name:";
			// 
			// txtContactEmail
			// 
			this->txtContactEmail->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtContactEmail->Location = System::Drawing::Point(207, 108);
			this->txtContactEmail->Margin = System::Windows::Forms::Padding(4);
			this->txtContactEmail->Name = L"txtContactEmail";
			this->txtContactEmail->Size = System::Drawing::Size(327, 23);
			this->txtContactEmail->TabIndex = 30;
			// 
			// txtContactPhoneNum
			// 
			this->txtContactPhoneNum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtContactPhoneNum->Location = System::Drawing::Point(24, 108);
			this->txtContactPhoneNum->Margin = System::Windows::Forms::Padding(4);
			this->txtContactPhoneNum->Name = L"txtContactPhoneNum";
			this->txtContactPhoneNum->Size = System::Drawing::Size(173, 23);
			this->txtContactPhoneNum->TabIndex = 29;
			// 
			// txtContactLastName
			// 
			this->txtContactLastName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtContactLastName->Location = System::Drawing::Point(207, 52);
			this->txtContactLastName->Margin = System::Windows::Forms::Padding(4);
			this->txtContactLastName->Name = L"txtContactLastName";
			this->txtContactLastName->Size = System::Drawing::Size(261, 23);
			this->txtContactLastName->TabIndex = 28;
			// 
			// txtContactFirstName
			// 
			this->txtContactFirstName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->txtContactFirstName->Location = System::Drawing::Point(24, 52);
			this->txtContactFirstName->Margin = System::Windows::Forms::Padding(4);
			this->txtContactFirstName->Name = L"txtContactFirstName";
			this->txtContactFirstName->Size = System::Drawing::Size(173, 23);
			this->txtContactFirstName->TabIndex = 27;
			// 
			// gbWebsite
			// 
			this->gbWebsite->Controls->Add(this->lblWebURL);
			this->gbWebsite->Controls->Add(this->txtWebURL);
			this->gbWebsite->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gbWebsite->Location = System::Drawing::Point(976, 244);
			this->gbWebsite->Margin = System::Windows::Forms::Padding(4);
			this->gbWebsite->Name = L"gbWebsite";
			this->gbWebsite->Padding = System::Windows::Forms::Padding(4);
			this->gbWebsite->Size = System::Drawing::Size(307, 102);
			this->gbWebsite->TabIndex = 22;
			this->gbWebsite->TabStop = false;
			this->gbWebsite->Text = L"Website Properties";
			// 
			// lblWebURL
			// 
			this->lblWebURL->AutoSize = true;
			this->lblWebURL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblWebURL->Location = System::Drawing::Point(8, 31);
			this->lblWebURL->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblWebURL->Name = L"lblWebURL";
			this->lblWebURL->Size = System::Drawing::Size(95, 17);
			this->lblWebURL->TabIndex = 13;
			this->lblWebURL->Text = L"Website URL:";
			// 
			// txtWebURL
			// 
			this->txtWebURL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtWebURL->Location = System::Drawing::Point(12, 55);
			this->txtWebURL->Margin = System::Windows::Forms::Padding(4);
			this->txtWebURL->Name = L"txtWebURL";
			this->txtWebURL->Size = System::Drawing::Size(272, 23);
			this->txtWebURL->TabIndex = 23;
			// 
			// gbDocument
			// 
			this->gbDocument->Controls->Add(this->lblDocPath);
			this->gbDocument->Controls->Add(this->txtDocPath);
			this->gbDocument->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->gbDocument->Location = System::Drawing::Point(669, 244);
			this->gbDocument->Margin = System::Windows::Forms::Padding(4);
			this->gbDocument->Name = L"gbDocument";
			this->gbDocument->Padding = System::Windows::Forms::Padding(4);
			this->gbDocument->Size = System::Drawing::Size(299, 102);
			this->gbDocument->TabIndex = 20;
			this->gbDocument->TabStop = false;
			this->gbDocument->Text = L"Document Properties";
			// 
			// lblDocPath
			// 
			this->lblDocPath->AutoSize = true;
			this->lblDocPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblDocPath->Location = System::Drawing::Point(20, 27);
			this->lblDocPath->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblDocPath->Name = L"lblDocPath";
			this->lblDocPath->Size = System::Drawing::Size(41, 17);
			this->lblDocPath->TabIndex = 12;
			this->lblDocPath->Text = L"Path:";
			// 
			// txtDocPath
			// 
			this->txtDocPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtDocPath->Location = System::Drawing::Point(24, 55);
			this->txtDocPath->Margin = System::Windows::Forms::Padding(4);
			this->txtDocPath->Name = L"txtDocPath";
			this->txtDocPath->Size = System::Drawing::Size(255, 23);
			this->txtDocPath->TabIndex = 21;
			// 
			// lblResultCount
			// 
			this->lblResultCount->AutoSize = true;
			this->lblResultCount->Location = System::Drawing::Point(9, 25);
			this->lblResultCount->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblResultCount->Name = L"lblResultCount";
			this->lblResultCount->Size = System::Drawing::Size(54, 13);
			this->lblResultCount->TabIndex = 0;
			this->lblResultCount->Text = L"Results: 0";
			// 
			// gbNodeInfo
			// 
			this->gbNodeInfo->Controls->Add(this->lblNodeCount);
			this->gbNodeInfo->Controls->Add(this->lblResultCount);
			this->gbNodeInfo->Location = System::Drawing::Point(10, 551);
			this->gbNodeInfo->Margin = System::Windows::Forms::Padding(4);
			this->gbNodeInfo->Name = L"gbNodeInfo";
			this->gbNodeInfo->Padding = System::Windows::Forms::Padding(4);
			this->gbNodeInfo->Size = System::Drawing::Size(271, 75);
			this->gbNodeInfo->TabIndex = 26;
			this->gbNodeInfo->TabStop = false;
			this->gbNodeInfo->Text = L"Results Information";
			// 
			// lblNodeCount
			// 
			this->lblNodeCount->AutoSize = true;
			this->lblNodeCount->Location = System::Drawing::Point(11, 41);
			this->lblNodeCount->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblNodeCount->Name = L"lblNodeCount";
			this->lblNodeCount->Size = System::Drawing::Size(43, 13);
			this->lblNodeCount->TabIndex = 1;
			this->lblNodeCount->Text = L"Total: 0";
			// 
			// btnModifyToggle
			// 
			this->btnModifyToggle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnModifyToggle->Location = System::Drawing::Point(603, 271);
			this->btnModifyToggle->Margin = System::Windows::Forms::Padding(4);
			this->btnModifyToggle->Name = L"btnModifyToggle";
			this->btnModifyToggle->Size = System::Drawing::Size(41, 58);
			this->btnModifyToggle->TabIndex = 5;
			this->btnModifyToggle->Text = L"<<";
			this->btnModifyToggle->UseVisualStyleBackColor = true;
			this->btnModifyToggle->Click += gcnew System::EventHandler(this, &MainWindow::btnModifyToggle_Click);
			// 
			// btnExit
			// 
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnExit->Location = System::Drawing::Point(594, 568);
			this->btnExit->Margin = System::Windows::Forms::Padding(4);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(50, 44);
			this->btnExit->TabIndex = 8;
			this->btnExit->Text = L"Quit";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainWindow::btnExit_Click);
			// 
			// btnNewEntry
			// 
			this->btnNewEntry->Location = System::Drawing::Point(996, 372);
			this->btnNewEntry->Name = L"btnNewEntry";
			this->btnNewEntry->Size = System::Drawing::Size(120, 30);
			this->btnNewEntry->TabIndex = 9;
			this->btnNewEntry->Text = L"New Entry";
			this->btnNewEntry->UseVisualStyleBackColor = true;
			this->btnNewEntry->Click += gcnew System::EventHandler(this, &MainWindow::btnNewEntry_Click);
			// 
			// btnResetEntry
			// 
			this->btnResetEntry->Location = System::Drawing::Point(1135, 372);
			this->btnResetEntry->Name = L"btnResetEntry";
			this->btnResetEntry->Size = System::Drawing::Size(120, 30);
			this->btnResetEntry->TabIndex = 10;
			this->btnResetEntry->Text = L"Clear Fields";
			this->btnResetEntry->UseVisualStyleBackColor = true;
			this->btnResetEntry->Click += gcnew System::EventHandler(this, &MainWindow::btnResetEntry_Click);
			// 
			// btnSaveEntry
			// 
			this->btnSaveEntry->Location = System::Drawing::Point(996, 417);
			this->btnSaveEntry->Name = L"btnSaveEntry";
			this->btnSaveEntry->Size = System::Drawing::Size(120, 30);
			this->btnSaveEntry->TabIndex = 11;
			this->btnSaveEntry->Text = L"Save Entry";
			this->btnSaveEntry->UseVisualStyleBackColor = true;
			this->btnSaveEntry->Click += gcnew System::EventHandler(this, &MainWindow::btnSaveEntry_Click);
			// 
			// btnDeleteEntry
			// 
			this->btnDeleteEntry->Location = System::Drawing::Point(1135, 417);
			this->btnDeleteEntry->Name = L"btnDeleteEntry";
			this->btnDeleteEntry->Size = System::Drawing::Size(120, 30);
			this->btnDeleteEntry->TabIndex = 12;
			this->btnDeleteEntry->Text = L"Delete Entry";
			this->btnDeleteEntry->UseVisualStyleBackColor = true;
			this->btnDeleteEntry->Click += gcnew System::EventHandler(this, &MainWindow::btnDeleteEntry_Click);
			// 
			// MainWindow
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1324, 663);
			this->ControlBox = false;
			this->Controls->Add(this->btnDeleteEntry);
			this->Controls->Add(this->btnSaveEntry);
			this->Controls->Add(this->btnResetEntry);
			this->Controls->Add(this->btnNewEntry);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->btnModifyToggle);
			this->Controls->Add(this->gbPicture);
			this->Controls->Add(this->gbContact);
			this->Controls->Add(this->gbWebsite);
			this->Controls->Add(this->gbDocument);
			this->Controls->Add(this->lblAddEdit);
			this->Controls->Add(this->gbNode);
			this->Controls->Add(this->cbCategories);
			this->Controls->Add(this->gbNodeInfo);
			this->Controls->Add(this->gbFeatures);
			this->Controls->Add(this->gbResults);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->txtSearch);
			this->Controls->Add(this->lblCategories);
			this->Controls->Add(this->lblSearch);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainWindow";
			this->Text = L"Quasar";
			this->Deactivate += gcnew System::EventHandler(this, &MainWindow::MainWindow_Deactivate);
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			this->gbResults->ResumeLayout(false);
			this->gbFeatures->ResumeLayout(false);
			this->gbNode->ResumeLayout(false);
			this->gbNode->PerformLayout();
			this->gbPicture->ResumeLayout(false);
			this->gbPicture->PerformLayout();
			this->gbContact->ResumeLayout(false);
			this->gbContact->PerformLayout();
			this->gbWebsite->ResumeLayout(false);
			this->gbWebsite->PerformLayout();
			this->gbDocument->ResumeLayout(false);
			this->gbDocument->PerformLayout();
			this->gbNodeInfo->ResumeLayout(false);
			this->gbNodeInfo->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void MainWindow_Load(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e) {
			 txtSearch->SelectionStart = 0;
			 txtSearch->SelectionLength = txtSearch->TextLength;
			 int category = getCategoryIndex();
			 nm->goFirst(category);
			 if(!nm->outOfBounds())	// if there are nodes to search through
			 {
				Node *current;
				SearchManager sm;
				string std_value;
				MarshalString(txtSearch->Text, std_value);
				results->clear();
				sm.identifySearchCriteria(std_value);
				while(!nm->outOfBounds()){
					current = nm->getCurrentNode();
					sm.setCurrent(current);
					if(sm.isMatched())
						results->push_back(current);
					nm->goNext(category);
				}
				updateResultCountLabel(results->size());
				showResults();
			 }
		 }
		 private:
			 void openBrowser(Node* cur, String^ browser)
			 {
				 if(cur)
				 {
					 if(cur->website)
					 {
						 string url = cur->website->getSiteURL();
						 String^ webURL = gcnew String(url.c_str());
						 System::Diagnostics::Process::Start(browser, webURL);
					 }
					 else
						 System::Diagnostics::Process::Start(browser, "https://duckduckgo.com/");
				 }
				 else
					 System::Diagnostics::Process::Start(browser, "https://duckduckgo.com/");
			 }
private: System::Void btnResearch_Click(System::Object^  sender, System::EventArgs^  e) {
			 // (extra feature) search the internet when this button is clicked
			 String^ browser = "IExplore.exe";
			 try
			 {
				 openBrowser(activeNode, browser);
			 }
			 catch(Exception^ exp)
			 {
				 browser = "Firefox.exe";
				 openBrowser(activeNode, browser);
			 }
		 }
private: System::Void lstResults_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 }
private: System::Void cbCategories_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
			 bool resetText = true;
			 for(int i=0; i<cbCategories->Items->Count; i++)
				 if(cbCategories->Text == cbCategories->Items[i]) resetText = false;
			 if(resetText) cbCategories->Text = "All Categories";
		 }
private: System::Void cbCategories_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void btnSave_Click(System::Object^  sender, System::EventArgs^  e) {
			 // save data to file
			 if(!nm->isEmpty())
				 nm->_saveNodeStructure();
		 }
private: System::Void btnModifyToggle_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->Width == (gbNode->Left + 6)){
				btnModifyToggle->Text = "<<";
				this->Width = (gbNode->Left + gbNode->Width + 24 );
				} else {
				btnModifyToggle->Text = ">>";
				this->Width = (gbNode->Left + 6);
			 }
		 }
private: System::Void MainWindow_Deactivate(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void btnExit_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!nm->isEmpty())
				 nm->_saveNodeStructure();
			 exit(0);
		 }

		 private:
			 // refill the lstResults GUI component with entries
			 void reloadListBox()
			 {
				 int category = getCategoryIndex();
				 results->clear();
				 nm->goFirst(category);
				 while(!nm->outOfBounds()){
					results->push_back(nm->getCurrentNode());
					nm->goNext(category);
				 }
				 updateResultCountLabel(results->size());
				 updateNodeCountLabel(results->size());
				 showResults();
			 }

private: System::Void btnShowAll_Click(System::Object^  sender, System::EventArgs^  e) {
			 reloadListBox();
		 }
private: System::Void btnResetEntry_Click(System::Object^  sender, System::EventArgs^  e) {
			 resetNodeFields();
			 resetActiveNode();
		 }
private: System::Void btnNewEntry_Click(System::Object^  sender, System::EventArgs^  e) {
			resetNodeFields();
			resetActiveNode();
			txtNodeTitle->Text = "[New Node]";
			activeNode = new Node;
			fillActiveNode();
			addActiveNode();
			reloadListBox();
		 }
private: System::Void btnDeleteEntry_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(activeNode)
				 nm->deleteNode(activeNode);
			 activeNode = NULL;
			 resetNodeFields();
			 reloadListBox();
		 }

private: System::Void btnSaveEntry_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!activeNode){	// if active node is null
				if(txtNodeTitle->Text == "") return;
				activeNode = new Node;
				fillActiveNode();		// create new node and add
				addActiveNode();
			 }
			 else	// else check for data change (i.e. was doc, now doc and web)
			 {
				 unsigned char previousNodeType = activeNode->getNodeType();
				 fillActiveNode();	// update existing
				 
				 if(activeNode->getNodeType() != previousNodeType)	// if there is a change
				 {
					 // save all data
					 nm->_saveNodeStructure();
					 // delete entire list
					 delete nm;
					 nm = NULL;
					 // create a new one
					 nm = new NodeManager("Quasar.dat");
				 }
			 }
			 reloadListBox();
		}
private: System::Void lstResults_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void lstResults_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			 if(lstResults->SelectedIndex != -1)
			 {
				 activeNode = results->at(lstResults->SelectedIndex);
				 setNodeFields();
				 // expand edit fields
				 if(this->Width == (gbNode->Left + 6))
				 {
					 btnModifyToggle->Text = "<<";
					 this->Width = (gbNode->Left + gbNode->Width + 24 );
				 }
			 }
		 }
private: System::Void btnSetDate_Click(System::Object^  sender, System::EventArgs^  e) {
			 txtNodeDate->Text = datePicker->Text;
		 }
private: System::Void txtSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void txtSearch_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 if(e->KeyChar == 13)
			 {
				 e->Handled = true;
				 btnSearch_Click(sender, e);
			 }
		 }
private: System::Void gbNode_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

#endif