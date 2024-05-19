#pragma once
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "GameSettings.h"

class DrawingPanel : public wxPanel
{
private:
	wxWindow* pMainWindow;
	std::vector<std::vector<bool>>& rGameBoard;
	GameSettings* pSettings;

	void OnPaint(wxPaintEvent& paintEvent);
	void OnMouseUp(wxMouseEvent& mouseEvent);
public:
	void SetGridSize(int& gridSize);
	void SetPanelSize(wxSize& panelSize);
	DrawingPanel(wxWindow* mainWindowPtr, std::vector<std::vector<bool>>& gameBoard, GameSettings& settings);
	~DrawingPanel();
	wxDECLARE_EVENT_TABLE();
};