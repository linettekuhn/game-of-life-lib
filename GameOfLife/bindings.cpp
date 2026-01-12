#include <emscripten/bind.h>
#include "GameBoard.h"
#include "GameSettings.h"
#include "Types.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(Types) {
    value_object<Types::Color>("Color")
        .field("r", &Types::Color::r)
        .field("g", &Types::Color::g)
        .field("b", &Types::Color::b)
        .field("a", &Types::Color::a);

    value_object<Types::Size>("Size")
        .field("x", &Types::Size::x)
        .field("y", &Types::Size::y);
}

EMSCRIPTEN_BINDINGS(GameSettings) {
    value_object<GameSettings>("GameSettings")
        .field("livingCellRed", &GameSettings::livingCellRed)
        .field("livingCellGreen", &GameSettings::livingCellGreen)
        .field("livingCellBlue", &GameSettings::livingCellBlue)
        .field("livingCellAlpha", &GameSettings::livingCellAlpha)
        .field("deadCellRed", &GameSettings::deadCellRed)
        .field("deadCellGreen", &GameSettings::deadCellGreen)
        .field("deadCellBlue", &GameSettings::deadCellBlue)
        .field("deadCellAlpha", &GameSettings::deadCellAlpha)
        .field("gridLineRed", &GameSettings::gridLineRed)
        .field("gridLineGreen", &GameSettings::gridLineGreen)
        .field("gridLineBlue", &GameSettings::gridLineBlue)
        .field("gridLineAlpha", &GameSettings::gridLineAlpha)
        .field("gridSize", &GameSettings::gridSize)
        .field("interval", &GameSettings::interval)
        .field("isHUDChecked", &GameSettings::isHUDChecked)
        .field("isNeighborCountChecked", &GameSettings::isNeighborCountChecked)
        .field("isToroidalChecked", &GameSettings::isToroidalChecked)
        .field("isShowGridChecked", &GameSettings::isShowGridChecked)
        .field("isShowThickGridChecked", &GameSettings::isShowThickGridChecked)
        .field("windowWidth", &GameSettings::windowWidth)
        .field("windowHeight", &GameSettings::windowHeight);
}

EMSCRIPTEN_BINDINGS(GameBoard) {
    class_<GameBoard>("GameBoard")
        .constructor<>()
        .function("RandomizeGameBoard", &GameBoard::RandomizeGameBoard)
        .function("NextGeneration", &GameBoard::NextGeneration)
        .function("InitializeGameBoard", &GameBoard::InitializeGameBoard)
        .function("LivingNeighborCount", &GameBoard::LivingNeighborCount)
        .function("UpdateCounts", &GameBoard::UpdateCounts)
        .function("ClearUniverse", &GameBoard::ClearUniverse)
        .function("getGameBoardPointer", &GameBoard::getGameBoardPointer)
        .function("getNeighborCountsPointer", &GameBoard::getNeighborCountsPointer)
        .function("getBoardSize", &GameBoard::getBoardSize)
        .function("setGameBoardFromPointer", &GameBoard::setGameBoardFromPointer)
        .property("mGenerationCount", &GameBoard::mGenerationCount)
        .property("mLivingCellCount", &GameBoard::mLivingCellCount)
        .property("mSettings", &GameBoard::mSettings);
}
