#pragma once
#include "wx/wx.h"
#include "wx/numdlg.h"
#include "wx/filedlg.h"
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
	wxMenu* pFileMenu;
	wxMenu* pViewMenu;
	wxMenu* pOptionsMenu;
	wxMenuItem* pNeighborCountMenuItem;
	wxTimer* pTimer;
	wxString mFilePath;
	
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
	void OnNewButtonClick(wxCommandEvent& newButtonEvent);
	void OnOpenButtonClick(wxCommandEvent& openButtonEvent);
	void OnSaveButtonClick(wxCommandEvent& saveButtonEvent);
	void OnSaveAsButtonClick(wxCommandEvent& saveAsButtonEvent);
	void OnExitButtonClick(wxCommandEvent& exitButtonEvent);

	void RandomizeGameBoard(int seed);
	void NextGeneration();
	void InitializeGameBoard();
	int LivingNeighborCount(int& row, int& col);
	void UpdateStatusBar();
	void RefreshMenuItems();
	void UpdateCounts();
	void ClearUniverse();
public:
	void Refresh(bool eraseBackground = true, const wxRect* rect = NULL);
	MainWindow();
	~MainWindow();
	wxDECLARE_EVENT_TABLE();
};

