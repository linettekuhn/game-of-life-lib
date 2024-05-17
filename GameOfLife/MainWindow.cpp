#include "MainWindow.h"

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

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 400)), pDrawingPanel(new DrawingPanel(this, mGameBoard)), mGridSize(15)
{
	Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
	InitializeGameBoard();
}

MainWindow::~MainWindow()
{

}
