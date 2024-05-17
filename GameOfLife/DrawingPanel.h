#pragma once
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

class DrawingPanel : public wxPanel
{
private:
	wxWindow* pMainWindow;
	int mGridSize;
	std::vector<std::vector<bool>>& rGameBoard;

	void OnPaint(wxPaintEvent& paintEvent);
	void OnMouseUp(wxMouseEvent& mouseEvent);
public:
	void SetGridSize(int& gridSize);
	void SetPanelSize(wxSize& panelSize);
	DrawingPanel(wxWindow* mainWindowPtr, std::vector<std::vector<bool>>& gameBoard);
	~DrawingPanel();
	wxDECLARE_EVENT_TABLE();
};