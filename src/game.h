#pragma once
#include "grid.h"
#include "blocks.cpp"

using namespace std;

class Game
{
public:
    Game();
    Grid grid;
    vector<Block> blocks;
    Block GetRandomBlock();
    void Draw();
    void HandleInput();

    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();

private:
    bool IsBlockOutside();
    void RotateBlockCW();
    void RotateBlockCCW();
    void RotateBlock180();

    vector<Block> GetAllBlocks();
    Block currentBlock;
    vector<Block> nextBlocks;
};
