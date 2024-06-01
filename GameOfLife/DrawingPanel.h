#pragma once
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "GameSettings.h"

class MainWindow;

class DrawingPanel : public wxPanel
{
private:
	MainWindow* pMainWindow;
	std::vector<std::vector<bool>>& rGameBoard;
	std::vector<std::vector<int>>& rNeighborCounts;
	GameSettings& rSettings;

	void OnPaint(wxPaintEvent& paintEvent);
	void OnMouseUp(wxMouseEvent& mouseEvent);
public:
	void SetPanelSize(const wxSize& panelSize);
	DrawingPanel(MainWindow* mainWindow, std::vector<std::vector<bool>>& gameBoard, GameSettings& settings, std::vector<std::vector<int>>& neighborCounts);
	~DrawingPanel();
	wxDECLARE_EVENT_TABLE();
};