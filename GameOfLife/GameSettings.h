#pragma once
#include "wx/wx.h"

struct GameSettings
{
	unsigned int livingCellRed = 128;
	unsigned int livingCellGreen = 128;	
	unsigned int livingCellBlue = 128;
	unsigned int livingCellAlpha = 255;
	
	unsigned int deadCellRed = 255;
	unsigned int deadCellGreen = 255;
	unsigned int deadCellBlue = 255;
	unsigned int deadCellAlpha = 255;

	int gridSize = 15;
	int interval = 50;

	wxColor GetLivingCellColor()
	{
		return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
	}
	wxColor GetDeadCellColor()
	{
		return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
	}
	void SetLivingCellColor(wxColor& color)
	{
		livingCellRed = color.GetRed();
		livingCellGreen = color.GetGreen();
		livingCellBlue = color.GetBlue();
		livingCellAlpha = color.GetAlpha();
	}
	void SetDeadCellColor(wxColor& color)
	{
		deadCellRed = color.GetRed();
		deadCellGreen = color.GetGreen();
		deadCellBlue = color.GetBlue();
		deadCellAlpha = color.GetAlpha();
	}
};
