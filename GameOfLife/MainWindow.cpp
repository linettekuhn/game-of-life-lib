#define TOOLBAR_PLAY_ICON 10001
#define TOOLBAR_NEXT_ICON 10002
#define TOOLBAR_PAUSE_ICON 10003
#define TOOLBAR_CLEAR_ICON 10004

#include "MainWindow.h"
#include "play.xpm"
#include "next.xpm"
#include "pause.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_MENU(TOOLBAR_PLAY_ICON, MainWindow::OnPlayButtonClick)
	EVT_MENU(TOOLBAR_NEXT_ICON, MainWindow::OnNextButtonClick)
	EVT_MENU(TOOLBAR_PAUSE_ICON, MainWindow::OnPauseButtonClick)
	EVT_MENU(TOOLBAR_CLEAR_ICON, MainWindow::OnClearButtonClick)
wxEND_EVENT_TABLE()

void MainWindow::OnSizeChange(wxSizeEvent& sizeEvent)
{
	wxSize windowSize = GetSize();
	if (pDrawingPanel != nullptr)
	{
		pDrawingPanel->SetPanelSize(windowSize);
	}
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

void MainWindow::OnPlayButtonClick(wxCommandEvent& playButtonEvent)
{
}

void MainWindow::NextGeneration()
{
	mLivingCellCount = 0;
	mGenerationCount++;
	std::vector<std::vector<bool>> sandbox;
	sandbox.resize(mGridSize);
	for (int i = 0; i < mGridSize; i++)
	{
		sandbox[i].resize(mGridSize);
	}

	for (int i = 0; i < mGridSize; i++)
	{
		for (int j = 0; j < mGridSize; j++)
		{
			int neighborCount = LivingNeighborCount(j, i);
			bool isAlive = mGameBoard[i][j];
			if (isAlive && (neighborCount == 2 || neighborCount == 3))
			{
				sandbox[i][j] = true;
				mLivingCellCount++;
			}
			else if (!isAlive && neighborCount == 3)
			{
				sandbox[i][j] = true;
				mLivingCellCount++;
			}
		}
	}
	mGameBoard.swap(sandbox);
	UpdateStatusBar();
	Refresh();
}

int MainWindow::LivingNeighborCount(int& row, int& col)
{
	int neighborCount = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int cellRow = row + j;
			int cellCol = col + i;
			
			if (i == 0 && j == 0) { continue; }
			if (cellRow < 0 || cellCol < 0) { continue; }
			if (cellRow >= mGridSize || cellCol >= mGridSize) { continue; }
		
			if (mGameBoard[cellCol][cellRow])
			{
				neighborCount++;
			}

		}
	}
	return neighborCount;
}

void MainWindow::OnNextButtonClick(wxCommandEvent& nextButtonEvent)
{
	NextGeneration();
}
void MainWindow::OnPauseButtonClick(wxCommandEvent& pauseButtonEvent)
{
}
void MainWindow::OnClearButtonClick(wxCommandEvent& clearButtonEvent)
{
	for (int i = 0; i < mGameBoard.size(); i++)
	{
		for (int j = 0; j < mGameBoard[i].size(); j++)
		{
			mGameBoard[i][j] = false;
		}
	}
	mLivingCellCount = 0;
	mGenerationCount = 0;
	UpdateStatusBar();
	Refresh();
}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)), pDrawingPanel(new DrawingPanel(this, mGameBoard)), mGridSize(15)
{
	wxBitmap playIcon(play_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap clearIcon(trash_xpm);

	pToolBar = CreateToolBar();
	pToolBar->AddTool(TOOLBAR_PLAY_ICON, "Play", playIcon);
	pToolBar->AddTool(TOOLBAR_NEXT_ICON, "Next", nextIcon);
	pToolBar->AddTool(TOOLBAR_PAUSE_ICON, "Pause", pauseIcon);
	pToolBar->AddTool(TOOLBAR_CLEAR_ICON, "Clear", clearIcon);
	pToolBar->Realize();

	pStatusBar = CreateStatusBar();
	UpdateStatusBar();

	InitializeGameBoard();

	Layout();
}

MainWindow::~MainWindow()
{

}
