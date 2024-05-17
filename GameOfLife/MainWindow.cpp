#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()

void MainWindow::OnSizeChange(wxSizeEvent& sizeEvent)
{
	wxSize windowSize = GetSize();
	pDrawingPanel->SetPanelSize(windowSize);
	sizeEvent.Skip();
	Refresh();
}

void MainWindow::InitializeGameBoard()
{
	mGameBoard.resize(mGridSize);
	for (int i = 0; i < mGridSize; i++)
	{
		mGameBoard[i].resize(mGridSize);
	}
	pDrawingPanel->SetGridSize(mGridSize);
}

void MainWindow::UpdateStatusBar()
{
	pStatusBar->SetFieldsCount(2);
	pStatusBar->SetStatusText(wxString::Format("No. of Generations: %d", mGenerationCount), 0);
	pStatusBar->SetStatusText(wxString::Format("Living Cell Count: %d", mLivingCellCount), 1);
}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 400)), pDrawingPanel(new DrawingPanel(this, mGameBoard)), mGridSize(15)
{
	pStatusBar = CreateStatusBar();
	UpdateStatusBar();
	InitializeGameBoard();
	Layout();
}

MainWindow::~MainWindow()
{

}
