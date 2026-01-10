#pragma once
#include <fstream>
#include "Types.h"

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

	Types::Color GetLivingCellColor() const
	{
		return { livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha };
	}
	Types::Color GetDeadCellColor() const
	{
		return { deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha };
	}
	Types::Color GetGridLineColor() const
	{
		return { gridLineRed, gridLineGreen, gridLineBlue, gridLineAlpha };
	}
	Types::Size GetWindowSize() const
	{
		return { windowWidth, windowHeight };
	}
	void SetLivingCellColor(const Types::Color& color)
	{
		livingCellRed = color.r;
		livingCellGreen = color.g;
		livingCellBlue = color.b;
		livingCellAlpha = color.a;
	}
	void SetDeadCellColor(const Types::Color& color)
	{
		deadCellRed = color.r;
		deadCellGreen = color.g;
		deadCellBlue = color.b;
		deadCellAlpha = color.a;
	}
	void SetGridLineColor(const Types::Color& color)
	{
		gridLineRed = color.r;
		gridLineGreen = color.g;
		gridLineBlue = color.b;
		gridLineAlpha = color.a;
	}
	void SetWindowSize(const Types::Size & size)
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
