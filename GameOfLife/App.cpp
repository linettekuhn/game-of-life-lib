#include "App.h"

wxIMPLEMENT_APP(App);

App::App() 
{

}

App::~App() 
{

}

bool App::OnInit() 
{
	mainWindowPtr = new MainWindow();
	mainWindowPtr->Show();
	return true;
}