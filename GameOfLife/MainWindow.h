#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
	
	void OnSizeChange(wxSizeEvent& sizeEvent);
public:
	MainWindow();
	~MainWindow();
};

