#pragma once
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
class DrawingPanel : public wxPanel
{
private:
	int mGridSize;
	std::vector<std::vector<bool>> mGameBoard;

	void OnPaint(wxPaintEvent& paintEvent);
public:
	void InitializeGameBoard(int& gridSize);
	void SetGridSize(int& gridSize);
	void SetPanelSize(wxSize& panelSize);
	DrawingPanel(wxWindow* mainWindowPtr);
	~DrawingPanel();
};