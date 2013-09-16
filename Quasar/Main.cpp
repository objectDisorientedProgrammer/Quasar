/*---------------------------------------------
 
  Filename:  main.cpp
  Team:     Gamma

  Date: 5/5/2013

  Update:  5/6/2013  sc
    Added EditWindow.h Winform to Quasar Project
	to display the node and category properties
	contained inside a node object.

  Updated:  5/8/2013 sc
    Added MarshalString.h to project
	Added #include "MarshalString.h" to main.cpp file

  Description:
    main() function. 

	The entry point for the
	Quasar program.  the OS launches the first
	thread for the entry point main(). A second thread
	launches the splash page which persists for 3000msecs.  
	
	The Splash page thread closes and the OS returns to the
	first thread to continue runtime execution. sc

	Added editWindow.h form 



---------------------------------------------*/


#include "ContactData.h"
#include "DocumentData.h"
#include "PictureData.h"
#include "WebsiteData.h"

#include "Node.h"

#include "Splash.h"
#include "MainWindow.h"

#include "time.h"
#include <vector>
#include <cstdlib>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

	Quasar::Splash splashForm;
    Application::Run(%splashForm);
	
	Quasar::MainWindow mainForm;
	Application::Run(%mainForm);

}  // end of main
