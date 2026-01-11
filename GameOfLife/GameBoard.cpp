#include "GameBoard.h"

void GameBoard::RandomizeGameBoard(int seed)
{
	srand(seed);
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			if ((rand() % 100) < 45)
			{
				mGameBoard[i][j] = true;
			}
			else
			{
				mGameBoard[i][j] = false;
			}
		}
	}
	UpdateCounts();
}

void GameBoard::NextGeneration()
{
	mGenerationCount++;
	std::vector<std::vector<bool>> sandbox;
	sandbox.resize(mSettings.gridSize);
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		sandbox[i].resize(mSettings.gridSize);
	}

	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			int neighborCount = LivingNeighborCount(j, i);
			bool isAlive = mGameBoard[i][j];
			if (isAlive && (neighborCount == 2 || neighborCount == 3))
			{
				sandbox[i][j] = true;
			}
			else if (!isAlive && neighborCount == 3)
			{
				sandbox[i][j] = true;
			}
		}
	}
	mGameBoard.swap(sandbox);
	UpdateCounts();
}

void GameBoard::InitializeGameBoard()
{
	mGameBoard.resize(mSettings.gridSize);
	mNeighborCounts.resize(mSettings.gridSize);
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		mGameBoard[i].resize(mSettings.gridSize);
		mNeighborCounts[i].resize(mSettings.gridSize);
	}
}

int GameBoard::LivingNeighborCount(int row, int col)
{
	int neighborCount = 0;
	
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int cellRow = row + j;
			int cellCol = col + i;
			
			if (mSettings.isToroidalChecked)
			{
				if (cellRow == -1)
				{
					cellRow = mSettings.gridSize - 1;
				}
				if (cellCol == -1)
				{
					cellCol = mSettings.gridSize - 1;
				}
				if (cellRow == mSettings.gridSize)
				{
					cellRow = 0;
				}
				if (cellCol == mSettings.gridSize)
				{
					cellCol = 0;
				}
			}

			if (i == 0 && j == 0) { continue; }
			if (cellRow < 0 || cellCol < 0) { continue; }
			if (cellRow >= mSettings.gridSize || cellCol >= mSettings.gridSize) { continue; }
			if (mGameBoard[cellCol][cellRow])
			{
				neighborCount++;
			}
		}
	}
	return neighborCount;
}

void GameBoard::UpdateCounts()
{
	mLivingCellCount = 0;
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			mNeighborCounts[i][j] = LivingNeighborCount(j, i);
			if (mGameBoard[i][j]) { mLivingCellCount++; }
		}
	}
}

void GameBoard::ClearUniverse()
{
	for (int i = 0; i < mGameBoard.size(); i++)
	{
		mGameBoard[i].clear();
		mNeighborCounts[i].clear();
	}
	mGameBoard.clear();
	mNeighborCounts.clear();

	mLivingCellCount = 0;
	mGenerationCount = 0;
}

GameBoard::GameBoard()
{	
	//load settings
	mSettings.LoadSettingsFile();

	//initialize gameboard
	InitializeGameBoard();

	UpdateCounts();
}
