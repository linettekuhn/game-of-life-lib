#pragma once

#include "GameSettings.h"
#include <vector>

class GameBoard {
public:
	std::vector<std::vector<bool>> mGameBoard;
	std::vector<std::vector<int>> mNeighborCounts;
	int mGenerationCount = 0;
	int mLivingCellCount = 0;
	GameSettings mSettings;

	uintptr_t getGameBoardPointer();
	uintptr_t getNeighborCountsPointer();
	int getBoardSize() const;
	void setGameBoardFromPointer(uintptr_t data, int size);

	void RandomizeGameBoard(int seed);
	void NextGeneration();
	void InitializeGameBoard();
	int LivingNeighborCount(int row, int col);
	void UpdateCounts();
	void ClearUniverse();

	GameBoard();

private:
	std::vector<uint8_t> mFlatGameBoard;
	std::vector<int> mFlatNeighborCounts;
	void syncFlatToGrid();
	void syncGridToFlat();
};

