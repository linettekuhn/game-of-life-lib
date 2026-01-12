#include "GameBoard.h"

uintptr_t GameBoard::getGameBoardPointer()
{
	syncGridToFlat();
	return reinterpret_cast<uintptr_t>(mFlatGameBoard.data());
}

uintptr_t GameBoard::getNeighborCountsPointer()
{
	return reinterpret_cast<uintptr_t>(mFlatNeighborCounts.data());
}

int GameBoard::getBoardSize() const
{
	return mSettings.gridSize * mSettings.gridSize;
}

void GameBoard::setGameBoardFromPointer(uintptr_t data, int size)
{
	if (size != getBoardSize()) {
		return;
	}

	uint8_t* dataPtr = reinterpret_cast<uint8_t*>(data);

	// Copy data into flat buffer
	for (int i = 0; i < size; i++) {
		mFlatGameBoard[i] = dataPtr[i];
	}

	// Sync to 2D grid
	syncFlatToGrid();
	UpdateCounts();
}

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
	syncGridToFlat();
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
	syncGridToFlat();
	UpdateCounts();
}

void GameBoard::InitializeGameBoard()
{
	mGameBoard.resize(mSettings.gridSize);
	mNeighborCounts.resize(mSettings.gridSize);
	mFlatGameBoard.resize(mSettings.gridSize * mSettings.gridSize);
	mFlatNeighborCounts.resize(mSettings.gridSize * mSettings.gridSize);

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
			mFlatNeighborCounts[i * mSettings.gridSize + j] = mNeighborCounts[i][j];
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
	mFlatGameBoard.clear();
	mFlatNeighborCounts.clear();

	mLivingCellCount = 0;
	mGenerationCount = 0;
}

GameBoard::GameBoard()
{	
	//load settings
	//mSettings.LoadSettingsFile();

	//initialize gameboard
	InitializeGameBoard();

	UpdateCounts();
}

void GameBoard::syncFlatToGrid()
{
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			mGameBoard[i][j] = mFlatGameBoard[i * mSettings.gridSize + j] != 0;
		}
	}
}

void GameBoard::syncGridToFlat()
{
	for (int i = 0; i < mSettings.gridSize; i++)
	{
		for (int j = 0; j < mSettings.gridSize; j++)
		{
			mGameBoard[i][j] = mFlatGameBoard[i * mSettings.gridSize + j] != 0;
		}
	}
}
