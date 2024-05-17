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
	
	float cellWidth = GetSize().x / (float)mGridSize;
	float cellHeight = GetSize().y / (float)mGridSize;

	//draw grid by drawing rectangles with loops
	for (int i = 0; i < mGridSize; i++)
	{
		for (int j = 0; j < mGridSize; j++)
		{
			bool isAlive = rGameBoard[i][j];
			if (isAlive)
			{
				//set the brush (fill of shape) to alive color
				graphicsContext->SetBrush(*wxYELLOW);
			}
			else
			{
				//set the brush (fill of shape) to dead color
				graphicsContext->SetBrush(*wxWHITE);
			}
			graphicsContext->DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
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
	int colIndex = mouseX / cellWidth;
	int rowIndex = mouseY / cellHeight;

	// flip the boolean value of the cell clicked
	//rGameBoard[colIndex][rowIndex] = !(rGameBoard[colIndex][rowIndex]);

	bool isAlive = rGameBoard[colIndex][rowIndex];
	if (isAlive)
	{
		rGameBoard[colIndex][rowIndex] = false;
	}
	else
	{
		rGameBoard[colIndex][rowIndex] = true;
	}

	pMainWindow->Refresh();
} 

void DrawingPanel::SetGridSize(int& gridSize)
{
	mGridSize = gridSize;
}

void DrawingPanel::SetPanelSize(wxSize& panelSize)
{
	SetSize(panelSize);
}

DrawingPanel::DrawingPanel(wxWindow* mainWindow, std::vector<std::vector<bool>>& gameBoard) : wxPanel(mainWindow, wxID_ANY, wxPoint(0, 0), mainWindow->GetSize()), mGridSize(0), rGameBoard(gameBoard), pMainWindow(mainWindow)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT); 
	Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this);
}

DrawingPanel::~DrawingPanel()
{

}
