#pragma once
#include "wx/wx.h"
#include <fstream>

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

	bool isNeighborCountChecked = false;

	wxColor GetLivingCellColor()
	{
		return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
	}
	wxColor GetDeadCellColor()
	{
		return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
	}
	void SetLivingCellColor(const wxColor& color)
	{
		livingCellRed = color.GetRed();
		livingCellGreen = color.GetGreen();
		livingCellBlue = color.GetBlue();
		livingCellAlpha = color.GetAlpha();
	}
	void SetDeadCellColor(const wxColor& color)
	{
		deadCellRed = color.GetRed();
		deadCellGreen = color.GetGreen();
		deadCellBlue = color.GetBlue();
		deadCellAlpha = color.GetAlpha();
	}
	void LoadSettingsFile()
	{
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		file.read((char*)this, sizeof(GameSettings));
		file.close();
	}
	void SaveSettingsFile()
	{
		std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
		file.write((char*)this, sizeof(GameSettings));
		file.close();
	}
	void RestoreSettings()
	{
		livingCellRed = 128;
		livingCellGreen = 128;
		livingCellBlue = 128;
		livingCellAlpha = 255;

		deadCellRed = 255;
		deadCellGreen = 255;
		deadCellBlue = 255;
		deadCellAlpha = 255;

		gridSize = 15;
		interval = 50;

		isNeighborCountChecked = false;

		SaveSettingsFile();
	}
};
