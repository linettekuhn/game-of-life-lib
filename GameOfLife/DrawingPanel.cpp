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
	
	float cellWidth = GetSize().x / (float)mGridSize;
	float cellHeight = GetSize().y / (float)mGridSize;

	//draw grid by drawing rectangles with loops
	for (int i = 0; i < mGridSize; i++)
	{
		for (int j = 0; j < mGridSize; j++)
		{
			graphicsContext->DrawRectangle(j * cellWidth, i * cellHeight, cellWidth, cellHeight);
		}
	}
}

void DrawingPanel::SetPanelSize(wxSize& panelSize)
{
	SetSize(panelSize);
}

DrawingPanel::DrawingPanel(wxWindow* mainWindow) : wxPanel(mainWindow, wxID_ANY, wxPoint(0, 0), mainWindow->GetSize()), mGridSize(15)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT); 
	Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{

}
