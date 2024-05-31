#define TIMER_ID 10000
#define TOOLBAR_PLAY_ICON_ID 10001
#define TOOLBAR_NEXT_ICON_ID 10002
#define TOOLBAR_PAUSE_ICON_ID 10003
#define TOOLBAR_CLEAR_ICON_ID 10004
#define OPTIONSMENU_SETTINGS_ID 10005
#define VIEWMENU_NEIGHBOR_ID 10006
#define OPTIONSMENU_RANDOM_TIME_ID 10007
#define OPTIONSMENU_RANDOM_SEED_ID 10008
#define VIEWMENU_FINITE_ID 10009
#define VIEWMENU_TORODIAL_ID 10010

#include "MainWindow.h"
#include "play.xpm"
#include "next.xpm"
#include "pause.xpm"
#include "trash.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_SIZE(MainWindow::OnSizeChange)
	EVT_TIMER(TIMER_ID, MainWindow::OnTimerStart)
	EVT_MENU(TOOLBAR_PLAY_ICON_ID, MainWindow::OnPlayButtonClick)
	EVT_MENU(TOOLBAR_NEXT_ICON_ID, MainWindow::OnNextButtonClick)
	EVT_MENU(TOOLBAR_PAUSE_ICON_ID, MainWindow::OnPauseButtonClick)
	EVT_MENU(TOOLBAR_CLEAR_ICON_ID, MainWindow::OnClearButtonClick)
	EVT_MENU(OPTIONSMENU_SETTINGS_ID, MainWindow::OnSettingsButtonClick)
	EVT_MENU(VIEWMENU_NEIGHBOR_ID, MainWindow::OnNeighborCountButtonClick)
	EVT_MENU(OPTIONSMENU_RANDOM_TIME_ID, MainWindow::OnRandomTimeButtonClick)
	EVT_MENU(OPTIONSMENU_RANDOM_SEED_ID, MainWindow::OnRandomSeedButtonClick)
	EVT_MENU(wxID_NEW, MainWindow::OnNewButtonClick)
	EVT_MENU(wxID_OPEN, MainWindow::OnOpenButtonClick)
	EVT_MENU(wxID_SAVE, MainWindow::OnSaveButtonClick)
	EVT_MENU(wxID_SAVEAS, MainWindow::OnSaveAsButtonClick)
	EVT_MENU(wxID_EXIT, MainWindow::OnExitButtonClick)
	EVT_MENU(VIEWMENU_FINITE_ID, MainWindow::OnFiniteButtonClick)
	EVT_MENU(VIEWMENU_TORODIAL_ID, MainWindow::OnTorodialButtonClick)
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

void MainWindow::OnTimerStart(wxTimerEvent& timerEvent)
{
	NextGeneration();
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
	ClearUniverse();
	InitializeGameBoard();
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
	mSettings.isNeighborCountChecked = pNeighborCountMenuItem->IsChecked();
	mSettings.SaveSettingsFile();
	Refresh();
}

void MainWindow::OnRandomTimeButtonClick(wxCommandEvent& randomTimeButtonEvent)
{
	RandomizeGameBoard(time(NULL));
}

void MainWindow::OnRandomSeedButtonClick(wxCommandEvent& randomSeedButtonEvent)
{
	long inputSeed = wxGetNumberFromUser("Enter a seed for the randomizer", "Seed:", "Custom Seed", time(NULL), 0, LONG_MAX, this);
	if (!(inputSeed == -1))
	{
		RandomizeGameBoard(inputSeed);
	}
}

void MainWindow::OnNewButtonClick(wxCommandEvent& newButtonEvent)
{
	pTimer->Stop();
	ClearUniverse();
	InitializeGameBoard();
	Refresh();
}

void MainWindow::OnOpenButtonClick(wxCommandEvent& openButtonEvent)
{
	pTimer->Stop();
	wxFileDialog openFileDialog(this, "Open Game of Life cells file", wxEmptyString, wxEmptyString, "Game of Life File (*.cells)|*.cells", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	int id = openFileDialog.ShowModal();
	if (id == wxID_CANCEL)
	{
		return;
	}

	ClearUniverse();

	int i = 0;
	std::string buffer;
	std::ifstream fileStream;
	fileStream.open((std::string)openFileDialog.GetPath());
	if (fileStream.is_open())
	{
		while (!fileStream.eof())
		{
			std::getline(fileStream, buffer);
			if (buffer.size() == 0) { break; }

			mSettings.gridSize = buffer.size();
			if (mGameBoard.size() == 0)
			{
				InitializeGameBoard();
			}

			for (int j = 0; j < buffer.size(); j++)
			{
				if (buffer[j] == '*')
				{
					mGameBoard[i][j] = true;
				}
				else
				{
					mGameBoard[i][j] = false;
				}
			}
			i++;
		}
		fileStream.close();
	}
	Refresh();
}

void MainWindow::OnSaveButtonClick(wxCommandEvent& saveButtonEvent)
{
	if (mFilePath == wxEmptyString)
	{
		wxFileDialog saveAsFileDialog(this, "Save Game of Life cells file", wxEmptyString, wxEmptyString, "Game of Life File (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		int id = saveAsFileDialog.ShowModal();
		if (id == wxID_CANCEL)
		{
			return;
		}
		mFilePath = saveAsFileDialog.GetPath();
	}
	std::ofstream fileStream;
	fileStream.open((std::string)mFilePath);
	if (fileStream.is_open())
	{
		for (int i = 0; i < mSettings.gridSize; i++)
		{
			for (int j = 0; j < mSettings.gridSize; j++)
			{
				if (mGameBoard[i][j])
				{
					fileStream << '*';
				}
				else
				{
					fileStream << '.';
				}
			}
			fileStream << '\n';
		}
		fileStream.close();
	}
}

void MainWindow::OnSaveAsButtonClick(wxCommandEvent& saveButtonEvent)
{
	wxFileDialog saveAsFileDialog(this, "Save Game of Life cells file", wxEmptyString, wxEmptyString, "Game of Life File (*.cells)|*.cells", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
	int id = saveAsFileDialog.ShowModal();
	if (id == wxID_CANCEL)
	{
		return;
	}
	mFilePath = saveAsFileDialog.GetPath();
	
	std::ofstream fileStream;
	fileStream.open((std::string)mFilePath);
	if (fileStream.is_open())
	{
		for (int i = 0; i < mSettings.gridSize; i++)
		{
			for (int j = 0; j < mSettings.gridSize; j++)
			{
				if (mGameBoard[i][j])
				{
					fileStream << '*';
				}
				else
				{
					fileStream << '.';
				}
			}
			fileStream << '\n';
		}
		fileStream.close();
	}
}

void MainWindow::OnExitButtonClick(wxCommandEvent& exitButtonEvent)
{
	Close();
}

void MainWindow::OnFiniteButtonClick(wxCommandEvent& finiteButtonEvent)
{
	mSettings.isTorodialChecked = false;
	mSettings.SaveSettingsFile();
	Refresh();
}

void MainWindow::OnTorodialButtonClick(wxCommandEvent& torodialButtonEvent)
{
	mSettings.isTorodialChecked = true;
	mSettings.SaveSettingsFile();
	Refresh();
}

void MainWindow::RandomizeGameBoard(int seed)
{
	srand(seed);
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			if ((rand() % 100) < 45)
			{
				mGameBoard[i][j] = true;
			}
			else
			{
				mGameBoard[i][j] = false;
			}
		}
	}
	Refresh();
}

void MainWindow::NextGeneration()
{
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
			}
			else if (!isAlive && neighborCount == 3)
			{
				sandbox[i][j] = true;
			}
		}
	}
	mGameBoard.swap(sandbox);
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

int MainWindow::LivingNeighborCount(int& row, int& col)
{
	int neighborCount = 0;
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int cellRow = row + j;
			int cellCol = col + i;
			
			if (mSettings.isTorodialChecked)
			{
				if (cellRow == -1)
				{
					cellRow = mSettings.gridSize - 1;
				}
				if (cellCol == -1)
				{
					cellCol = mSettings.gridSize - 1;
				}
				if (cellRow == mSettings.gridSize)
				{
					cellRow = 0;
				}
				if (cellCol == mSettings.gridSize)
				{
					cellCol = 0;
				}
			}

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

void MainWindow::UpdateStatusBar()
{
	pStatusBar->SetFieldsCount(2);
	pStatusBar->SetStatusText(wxString::Format("No. of Generations: %d", mGenerationCount), 0);
	pStatusBar->SetStatusText(wxString::Format("Living Cell Count: %d", mLivingCellCount), 1);
}

void MainWindow::RefreshMenuItems()
{
	pNeighborCountMenuItem->Check(mSettings.isNeighborCountChecked);
	pFiniteMenuItem->Check(!(mSettings.isTorodialChecked));
	pTorodialMenuItem->Check(mSettings.isTorodialChecked);
}

void MainWindow::UpdateCounts()
{
	mLivingCellCount = 0;
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			mNeighborCounts[i][j] = LivingNeighborCount(j, i);
			if (mGameBoard[i][j]) { mLivingCellCount++; }
		}
	}
}

void MainWindow::ClearUniverse()
{
	for (int i = 0; i < mGameBoard.size(); i++)
	{
		mGameBoard[i].clear();
		mNeighborCounts[i].clear();
	}
	mGameBoard.clear();
	mNeighborCounts.clear();

	mLivingCellCount = 0;
	mGenerationCount = 0;
}

void MainWindow::Refresh(bool eraseBackground, const wxRect* rect)
{
	UpdateCounts();
	UpdateStatusBar();
	RefreshMenuItems();
	wxFrame::Refresh(eraseBackground, rect);
}

MainWindow::MainWindow() : 
	wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(500, 500)),
	pDrawingPanel(new DrawingPanel(this, mGameBoard, mSettings, mNeighborCounts)), 
	pTimer(new wxTimer(this, TIMER_ID)),
	pMenuBar(new wxMenuBar()),
	pFileMenu(new wxMenu()),
	pViewMenu(new wxMenu()),
	pOptionsMenu(new wxMenu()),
	mFilePath(wxEmptyString)
{	
	//status bar
	pStatusBar = CreateStatusBar();
	wxFrame::SetStatusBarPane(-1);

	//load settings
	mSettings.LoadSettingsFile();

	//toolbar
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

	//menu bar
	SetMenuBar(pMenuBar);

	//file menu
	pFileMenu->Append(wxID_NEW);
	pFileMenu->Append(wxID_OPEN);
	pFileMenu->Append(wxID_SAVE);
	pFileMenu->Append(wxID_SAVEAS);
	pFileMenu->Append(wxID_EXIT);

	pMenuBar->Append(pFileMenu, "File");

	//view menu
	pNeighborCountMenuItem = new wxMenuItem(pViewMenu, VIEWMENU_NEIGHBOR_ID, "Show Neighbor Count", wxEmptyString, wxITEM_CHECK);
	pNeighborCountMenuItem->SetCheckable(true);
	
	pViewMenu->Append(pNeighborCountMenuItem);

	wxMenu* universeTypeSubMenu = new wxMenu();
	pFiniteMenuItem = new wxMenuItem(universeTypeSubMenu, VIEWMENU_FINITE_ID, "Finite", wxEmptyString, wxITEM_CHECK);
	pFiniteMenuItem->SetCheckable(true);
	pTorodialMenuItem = new wxMenuItem(universeTypeSubMenu, VIEWMENU_TORODIAL_ID, "Torodial", wxEmptyString, wxITEM_CHECK);
	pTorodialMenuItem->SetCheckable(true);

	universeTypeSubMenu->Append(pFiniteMenuItem);
	universeTypeSubMenu->Append(pTorodialMenuItem);
	pViewMenu->AppendSubMenu(universeTypeSubMenu, "Universe Type");

	pMenuBar->Append(pViewMenu, "View");

	//options menu
	pOptionsMenu->Append(OPTIONSMENU_SETTINGS_ID, "Settings");

	wxMenu* randomSubMenu = new wxMenu();
	randomSubMenu->Append(OPTIONSMENU_RANDOM_TIME_ID, "Randomize (time)");
	randomSubMenu->Append(OPTIONSMENU_RANDOM_SEED_ID, "Randomize (seed)");
	pOptionsMenu->AppendSubMenu(randomSubMenu, "Randomize");

	pMenuBar->Append(pOptionsMenu, "Options");

	//initialize gameboard
	InitializeGameBoard();

	Layout();
 
	Refresh();
}

MainWindow::~MainWindow()
{
	delete pDrawingPanel;
	delete pTimer;
}
