#define TIMER_ID 10000
#define TOOLBAR_PLAY_ICON_ID 10001
#define TOOLBAR_NEXT_ICON_ID 10002
#define TOOLBAR_PAUSE_ICON_ID 10003
#define TOOLBAR_CLEAR_ICON_ID 10004
#define MENUBAR_SETTINGS_ID 10005
#define MENUBAR_NEIGHBOR_ID 10006

#include "MainWindow.h"
#include "play.xpm"
#include "next.xpm"
#include "pause.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_MENU(TOOLBAR_PLAY_ICON_ID, MainWindow::OnPlayButtonClick)
	EVT_MENU(TOOLBAR_NEXT_ICON_ID, MainWindow::OnNextButtonClick)
	EVT_MENU(TOOLBAR_PAUSE_ICON_ID, MainWindow::OnPauseButtonClick)
	EVT_MENU(TOOLBAR_CLEAR_ICON_ID, MainWindow::OnClearButtonClick)
	EVT_MENU(MENUBAR_SETTINGS_ID, MainWindow::OnSettingsButtonClick)
	EVT_MENU(MENUBAR_NEIGHBOR_ID, MainWindow::OnNeighborCountButtonClick)
	EVT_TIMER(TIMER_ID, MainWindow::OnTimerStart)
wxEND_EVENT_TABLE()

void MainWindow::OnSizeChange(wxSizeEvent& sizeEvent)
{
	wxSize windowSize = GetSize();
	if (pDrawingPanel != nullptr)
	{
		pDrawingPanel->SetPanelSize(windowSize);
	}
	sizeEvent.Skip();
	pDrawingPanel->Refresh();
}

void MainWindow::OnPlayButtonClick(wxCommandEvent& playButtonEvent)
{
	pTimer->Start(mSettings.interval);
}

void MainWindow::OnNextButtonClick(wxCommandEvent& nextButtonEvent)
{
	NextGeneration();
}

void MainWindow::OnPauseButtonClick(wxCommandEvent& pauseButtonEvent)
{
	pTimer->Stop();
}

void MainWindow::OnClearButtonClick(wxCommandEvent& clearButtonEvent)
{
	pTimer->Stop();
	for (int i = 0; i < mGameBoard.size(); i++)
	{
		for (int j = 0; j < mGameBoard[i].size(); j++)
		{
			mGameBoard[i][j] = false;
			mNeighborCounts[i][j] = 0;
		}
	}
	mLivingCellCount = 0;
	mGenerationCount = 0;
	Refresh();
}

void MainWindow::OnSettingsButtonClick(wxCommandEvent& settingsButtonEvent)
{
	SettingsDialog settingsDialog(this, mSettings);
	int id = settingsDialog.ShowModal();
	if (id == wxID_OK)
	{
		InitializeGameBoard();
		Refresh();
	}
}

void MainWindow::OnNeighborCountButtonClick(wxCommandEvent& neighborCountButtonEvent)
{
	UpdateNeighborCount();
	mSettings.isNeighborCountChecked = pNeighborCountMenuItem->IsChecked();
	mSettings.SaveSettingsFile();
	Refresh();
}

void MainWindow::OnTimerStart(wxTimerEvent& timerEvent)
{
	NextGeneration();
}

void MainWindow::NextGeneration()
{
	mLivingCellCount = 0;
	mGenerationCount++;
	std::vector<std::vector<bool>> sandbox;
	sandbox.resize(mSettings.gridSize);
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		sandbox[i].resize(mSettings.gridSize);
	}

	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
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
	UpdateNeighborCount();
	Refresh();
}

void MainWindow::InitializeGameBoard()
{
	mGameBoard.resize(mSettings.gridSize);
	mNeighborCounts.resize(mSettings.gridSize);
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		mGameBoard[i].resize(mSettings.gridSize);
		mNeighborCounts[i].resize(mSettings.gridSize);
	}
}

void MainWindow::UpdateStatusBar()
{
	pStatusBar->SetFieldsCount(2);
	pStatusBar->SetStatusText(wxString::Format("No. of Generations: %d", mGenerationCount), 0);
	pStatusBar->SetStatusText(wxString::Format("Living Cell Count: %d", mLivingCellCount), 1);
}

void MainWindow::RefreshMenuItems()
{
	pNeighborCountMenuItem->Check(mSettings.isNeighborCountChecked);
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
			if (cellRow >= mSettings.gridSize || cellCol >= mSettings.gridSize) { continue; }
		
			if (mGameBoard[cellCol][cellRow])
			{
				neighborCount++;
			}

		}
	}
	return neighborCount;
}

void MainWindow::UpdateNeighborCount()
{
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			mNeighborCounts[i][j] = LivingNeighborCount(j, i);
		}
	}
}

void MainWindow::UpdateLivingCellCount(bool isAlive)
{
	if (isAlive)
	{
		mLivingCellCount++;
	}
	else
	{
		mLivingCellCount--;
	}
}

void MainWindow::Refresh(bool eraseBackground, const wxRect* rect)
{
	wxFrame::Refresh(eraseBackground, rect);
	UpdateStatusBar();
	RefreshMenuItems();
}

MainWindow::MainWindow() : 
	wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)), 
	pDrawingPanel(new DrawingPanel(this, mGameBoard, mSettings, mNeighborCounts)), 
	pTimer(new wxTimer(this, TIMER_ID)),
	pMenuBar(new wxMenuBar()),
	pOptionsMenu(new wxMenu()),
	pViewMenu(new wxMenu())
{
	mSettings.LoadSettingsFile();
	wxBitmap playIcon(play_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap clearIcon(trash_xpm);

	pToolBar = CreateToolBar();
	pToolBar->SetToolBitmapSize(wxSize(30, 25));
	pToolBar->AddTool(TOOLBAR_PLAY_ICON_ID, "", playIcon, "Play");
	pToolBar->AddTool(TOOLBAR_NEXT_ICON_ID, "", nextIcon, "Next");
	pToolBar->AddTool(TOOLBAR_PAUSE_ICON_ID, "", pauseIcon, "Pause");
	pToolBar->AddTool(TOOLBAR_CLEAR_ICON_ID, "", clearIcon, "Clear");
	pToolBar->Realize();

	pStatusBar = CreateStatusBar();
	wxFrame::SetStatusBarPane(-1);

	SetMenuBar(pMenuBar);

	pNeighborCountMenuItem = new wxMenuItem(pViewMenu, MENUBAR_NEIGHBOR_ID, "Show Neighbor Count", wxEmptyString, wxITEM_CHECK);
	pNeighborCountMenuItem->SetCheckable(true);

	pViewMenu->Append(pNeighborCountMenuItem);
	pMenuBar->Append(pViewMenu, "View");

	pOptionsMenu->Append(MENUBAR_SETTINGS_ID, "Settings");
	pMenuBar->Append(pOptionsMenu, "Options");

	InitializeGameBoard();

	Layout();

	Refresh();
}

MainWindow::~MainWindow()
{
	delete pDrawingPanel;
	delete pTimer;
}
