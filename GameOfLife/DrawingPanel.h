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
	std::vector<std::vector<int>>& rNeighborCounts;
	GameSettings& rSettings;

	void OnPaint(wxPaintEvent& paintEvent);
	void OnMouseUp(wxMouseEvent& mouseEvent);
public:
	void SetPanelSize(wxSize& panelSize);
	DrawingPanel(wxWindow* mainWindowPtr, std::vector<std::vector<bool>>& gameBoard, GameSettings& settings, std::vector<std::vector<int>>& neighborCounts);
	~DrawingPanel();
	wxDECLARE_EVENT_TABLE();
};