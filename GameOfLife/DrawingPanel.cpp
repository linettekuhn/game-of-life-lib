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
	
	//draw grid by drawing rectangles with loops
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			graphicsContext->DrawRectangle(j * gridSize, i * gridSize, gridSize, gridSize);
		}
	}
}

DrawingPanel::DrawingPanel(wxWindow* mainWindow) : wxPanel(mainWindow, wxID_ANY, wxPoint(0, 0), mainWindow->GetSize()), gridSize(15)
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT); 
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{

}
