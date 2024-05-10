#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
	DrawingPanel* pDrawingPanel;
public:
	MainWindow();
	~MainWindow();
};

