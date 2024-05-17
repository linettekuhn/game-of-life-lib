#include "MainWindow.h"

void MainWindow::OnSizeChange(wxSizeEvent& sizeEvent)
{
	wxSize windowSize = GetSize();
	pDrawingPanel->SetPanelSize(windowSize);
	sizeEvent.Skip();
	Refresh();
}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(300, 234)), pDrawingPanel(new DrawingPanel(this))
{
	Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
}

MainWindow::~MainWindow()
{

}
