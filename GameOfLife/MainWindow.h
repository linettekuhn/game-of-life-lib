#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
	int mGridSize;
	std::vector<std::vector<bool>> mGameBoard;
	
	void OnSizeChange(wxSizeEvent& sizeEvent);
	void InitializeGameBoard();
public:
	MainWindow();
	~MainWindow();
};

