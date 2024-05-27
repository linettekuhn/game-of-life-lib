#pragma once
#include "wx/wx.h"
#include "wx/numdlg.h"
#include "DrawingPanel.h"
#include "GameSettings.h"
#include "SettingsDialog.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
	std::vector<std::vector<bool>> mGameBoard;
	std::vector<std::vector<int>> mNeighborCounts;
	int mGenerationCount = 0;
	int mLivingCellCount = 0;
	wxStatusBar* pStatusBar;
	wxToolBar* pToolBar;
	wxMenuBar* pMenuBar;
	wxMenu* pOptionsMenu;
	wxMenu* pViewMenu;
	wxMenuItem* pNeighborCountMenuItem;
	wxTimer* pTimer;
	
	GameSettings mSettings;

	void OnSizeChange(wxSizeEvent& sizeEvent);
	void OnTimerStart(wxTimerEvent& timerEvent);
	void OnPlayButtonClick(wxCommandEvent& playButtonEvent);
	void OnNextButtonClick(wxCommandEvent& nextButtonEvent);
	void OnPauseButtonClick(wxCommandEvent& pauseButtonEvent);
	void OnClearButtonClick(wxCommandEvent& clearButtonEvent);
	void OnSettingsButtonClick(wxCommandEvent& settingsButtonEvent);
	void OnNeighborCountButtonClick(wxCommandEvent& neighborCountButtonEvent);
	void OnRandomTimeButtonClick(wxCommandEvent& randomTimeButtonEvent);
	void OnRandomSeedButtonClick(wxCommandEvent& randomSeedButtonEvent);

	void RandomizeGameBoard(int seed);
	void NextGeneration();
	void InitializeGameBoard();
	void UpdateStatusBar();
	void RefreshMenuItems();
	int LivingNeighborCount(int& row, int& col);
	void Refresh(bool eraseBackground = true, const wxRect* rect = NULL);
public:
	void UpdateLivingCellCount(bool isAlive);
	void UpdateNeighborCount();
	MainWindow();
	~MainWindow();
	wxDECLARE_EVENT_TABLE();
};

