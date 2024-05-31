#include "DrawingPanel.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
	EVT_PAINT(DrawingPanel::OnPaint)
	EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

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
	graphicsContext->SetPen(rSettings.GetGridLineColor());
	
	float cellWidth = GetSize().x / (float)rSettings.gridSize;
	float cellHeight = GetSize().y / (float)rSettings.gridSize;

	//draw grid by drawing rectangles with loops
	for (int i = 0; i < rSettings.gridSize; i++)
	{
		for (int j = 0; j < rSettings.gridSize; j++)
		{
			bool isAlive = rGameBoard[i][j];
			if (isAlive)
			{
				//set the brush (fill of shape) to alive color
				graphicsContext->SetBrush(rSettings.GetLivingCellColor());
			}
			else
			{
				//set the brush (fill of shape) to dead color
				graphicsContext->SetBrush(rSettings.GetDeadCellColor());
			}
			graphicsContext->DrawRectangle(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
			
			if (rSettings.isNeighborCountChecked)
			{	
				graphicsContext->SetFont(wxFontInfo(16), *wxRED);
				int neighbors = rNeighborCounts[i][j];

				if (neighbors == 0) { continue; }

				wxString numberText(std::to_string(neighbors));

				double textWidth;
				double textHeight;

				graphicsContext->GetTextExtent(numberText, &textWidth, &textHeight);

				int x = (cellWidth * i) + (cellWidth / 2) - (textWidth / 2);
				int y = (cellHeight * j) + (cellHeight / 2) - (textHeight / 2);

				graphicsContext->DrawText(numberText, x, y);
			}
		}
	}

	delete graphicsContext;
}

void DrawingPanel::OnMouseUp(wxMouseEvent& mouseEvent)
{
	//store mouse's coordinates in separate variables
	int mouseX = mouseEvent.GetX();
	int mouseY = mouseEvent.GetY();

	//calculate cell's width and height
	float cellWidth = GetSize().x / (float)rSettings.gridSize;
	float cellHeight = GetSize().y / (float)rSettings.gridSize;

	// calculate index position of mouse by dividing the mouse's coordinates by the cell's dimensions
	int colIndex = mouseX / cellWidth;
	int rowIndex = mouseY / cellHeight;

	// flip the boolean value of the cell clicked
	rGameBoard[colIndex][rowIndex] = !rGameBoard[colIndex][rowIndex];

	pMainWindow->Refresh();
}

void DrawingPanel::SetPanelSize(wxSize& panelSize)
{
	SetSize(panelSize);
}

DrawingPanel::DrawingPanel(MainWindow* mainWindow, std::vector<std::vector<bool>>& gameBoard, GameSettings& settings, std::vector<std::vector<int>>& neighborCounts) :
	wxPanel(mainWindow, wxID_ANY, wxPoint(0, 0), mainWindow->GetSize()),  
	pMainWindow(mainWindow), 
	rGameBoard(gameBoard),
	rNeighborCounts(neighborCounts),
	rSettings(settings)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT); 
}

DrawingPanel::~DrawingPanel()
{
}
