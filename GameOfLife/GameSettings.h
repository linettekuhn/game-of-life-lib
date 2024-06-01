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

	unsigned int gridLineRed = 0;
	unsigned int gridLineGreen = 0;
	unsigned int gridLineBlue = 0;
	unsigned int gridLineAlpha = 255;

	int gridSize = 30;
	int interval = 50;
	
	bool isHUDChecked = true;
	bool isNeighborCountChecked = true;
	bool isToroidalChecked = false;
	bool isShowGridChecked = true;
	bool isShowThickGridChecked = true;

	int windowWidth = 700;
	int windowHeight = 800;

	wxColor GetLivingCellColor() const
	{
		return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
	}
	wxColor GetDeadCellColor() const
	{
		return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
	}
	wxColor GetGridLineColor() const
	{
		return wxColor(gridLineRed, gridLineGreen, gridLineBlue, gridLineAlpha);
	}
	wxSize GetWindowSize() const
	{
		return wxSize(windowWidth, windowHeight);
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
	void SetGridLineColor(const wxColor& color)
	{
		gridLineRed = color.GetRed();
		gridLineGreen = color.GetGreen();
		gridLineBlue = color.GetBlue();
		gridLineAlpha = color.GetAlpha();
	}
	void SetWindowSize(const wxSize& size)
	{
		windowWidth = size.x;
		windowHeight = size.y;
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

		gridLineRed = 0;
		gridLineGreen = 0;
		gridLineBlue = 0;
		gridLineAlpha = 255;

		gridSize = 30;
		interval = 50;

		isHUDChecked = true;
		isNeighborCountChecked = true;
		isToroidalChecked = false;
		isShowGridChecked = true;
		isShowThickGridChecked = true;
		
		windowWidth = 700;
		windowHeight = 800;

		SaveSettingsFile();
	}
};
