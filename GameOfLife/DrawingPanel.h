#pragma once
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
class DrawingPanel : public wxPanel
{
private:
	int mGridSize;

	void OnPaint(wxPaintEvent& paintEvent);
public:
	void SetPanelSize(wxSize& panelSize);
	DrawingPanel(wxWindow* mainWindowPtr);
	~DrawingPanel();
};