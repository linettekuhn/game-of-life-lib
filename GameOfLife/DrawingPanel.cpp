#include "DrawingPanel.h"

void DrawingPanel::InitializeGameBoard(int& gridSize)
{
	SetGridSize(gridSize);
	mGameBoard.resize(mGridSize);
	for (int i = 0; i < mGridSize; i++)
	{
		mGameBoard[i].resize(mGridSize);
	}
}

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

void DrawingPanel::OnMouseUp(wxMouseEvent& mouseEvent)
{
	//store mouse's coordinates in separate variables
	int mouseX = mouseEvent.GetX();
	int mouseY = mouseEvent.GetY();

	//calculate cell's width and height
	float cellWidth = GetSize().x / (float)mGridSize;
	float cellHeight = GetSize().y / (float)mGridSize;

	// calculate index position of mouse by dividing the mouse's coordinates by the cell's dimensions
	int rowIndex = mouseX / cellWidth;
	int colIndex = mouseY / cellHeight;

	// flip the boolean value of the cell clicked
	mGameBoard[colIndex][rowIndex] = !(mGameBoard[colIndex][rowIndex]);

	Refresh();
} 

void DrawingPanel::SetGridSize(int& gridSize)
{
	mGridSize = gridSize;
}

void DrawingPanel::SetPanelSize(wxSize& panelSize)
{
	SetSize(panelSize);
}

DrawingPanel::DrawingPanel(wxWindow* mainWindow, std::vector<std::vector<bool>>& gameBoard) : wxPanel(mainWindow, wxID_ANY, wxPoint(0, 0), mainWindow->GetSize()), mGridSize(0), rGameBoard(gameBoard)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT); 
	Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
}

DrawingPanel::~DrawingPanel()
{

}
