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
	wxMenuItem* pFiniteMenuItem;
	wxMenuItem* pTorodialMenuItem;
	wxMenuItem* pShowGridMenuItem;
	wxMenuItem* pShowThickGridMenuItem;
	wxTimer* pTimer;
	wxString mFilePath;
	
	GameSettings mSettings;

	void OnSizeChange(wxSizeEvent& sizeEvent);
	void OnTimerStart(wxTimerEvent& timerEvent);
	void OnPlayButtonClick(wxCommandEvent& buttonEvent);
	void OnNextButtonClick(wxCommandEvent& buttonEvent);
	void OnPauseButtonClick(wxCommandEvent& buttonEvent);
	void OnClearButtonClick(wxCommandEvent& buttonEvent);
	void OnSettingsButtonClick(wxCommandEvent& buttonEvent);
	void OnNeighborCountButtonClick(wxCommandEvent& buttonEvent);
	void OnRandomTimeButtonClick(wxCommandEvent& buttonEvent);
	void OnRandomSeedButtonClick(wxCommandEvent& buttonEvent);
	void OnNewButtonClick(wxCommandEvent& buttonEvent);
	void OnOpenButtonClick(wxCommandEvent& buttonEvent);
	void OnSaveButtonClick(wxCommandEvent& buttonEvent);
	void OnSaveAsButtonClick(wxCommandEvent& buttonEvent);
	void OnImportButtonClick(wxCommandEvent& buttonEvent);
	void OnExitButtonClick(wxCommandEvent& buttonEvent);
	void OnFiniteButtonClick(wxCommandEvent& buttonEvent);
	void OnTorodialButtonClick(wxCommandEvent& buttonEvent);
	void OnShowGridButtonClick(wxCommandEvent& buttonEvent);
	void OnShowThickGridButtonClick(wxCommandEvent& buttonEvent);

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

