#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include "GameSettings.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
	std::vector<std::vector<bool>> mGameBoard;
	int mGenerationCount = 0;
	int mLivingCellCount = 0;
	wxStatusBar* pStatusBar;
	wxToolBar* pToolBar;
	wxTimer* pTimer;
	GameSettings mSettings;

	void OnSizeChange(wxSizeEvent& sizeEvent);
	void OnPlayButtonClick(wxCommandEvent& playButtonEvent);
	void OnNextButtonClick(wxCommandEvent& nextButtonEvent);
	void OnPauseButtonClick(wxCommandEvent& pauseButtonEvent);
	void OnClearButtonClick(wxCommandEvent& clearButtonEvent);
	void OnTimerStart(wxTimerEvent& timerEvent);

	void NextGeneration();
	void InitializeGameBoard();
	void UpdateStatusBar();
	int LivingNeighborCount(int& row, int& col);
public:
	MainWindow();
	~MainWindow();
	wxDECLARE_EVENT_TABLE();
};

