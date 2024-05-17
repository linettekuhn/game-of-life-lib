#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
	int mGridSize;
	std::vector<std::vector<bool>> mGameBoard;
	int mGenerationCount = 0;
	int mLivingCellCount = 0;
	wxStatusBar* pStatusBar;
	wxToolBar* pToolBar;

	void OnSizeChange(wxSizeEvent& sizeEvent);
	
	void OnPlayButtonClick(wxCommandEvent& playButtonEvent);
	void OnNextButtonClick(wxCommandEvent& nextButtonEvent);
	void OnPauseButtonClick(wxCommandEvent& pauseButtonEvent);
	void OnClearButtonClick(wxCommandEvent& clearButtonEvent);
	
	void InitializeGameBoard();
	void UpdateStatusBar();
public:
	MainWindow();
	~MainWindow();
	wxDECLARE_EVENT_TABLE();
};

