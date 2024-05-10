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
	pMainWindow = new MainWindow();
	pMainWindow->Show();
	return true;
}