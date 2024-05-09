#include "DrawingPanel.h"

void DrawingPanel::OnPaint(wxPaintEvent& paintEvent)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();
	wxGraphicsContext* graphicsContext = wxGraphicsContext::Create(dc);
	if (!graphicsContext)
	{
		return;
	}
	//set the pen (outline of shape) color
	graphicsContext->SetPen(*wxLIGHT_GREY);
	//set the brush (fill of shape) color
	graphicsContext->SetBrush(*wxWHITE);
	graphicsContext->DrawRectangle(0, 0, 100, 100);
}

DrawingPanel::DrawingPanel(wxWindow* mainWindow) : wxPanel(mainWindow, wxID_ANY, wxPoint(0, 0), wxSize(300, 500))
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT); 
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{

}
