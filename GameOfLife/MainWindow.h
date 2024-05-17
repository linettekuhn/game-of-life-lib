#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
	int mGridSize;
	
	void OnSizeChange(wxSizeEvent& sizeEvent);
public:
	MainWindow();
	~MainWindow();
};

