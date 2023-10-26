#pragma once
#include "grid.h"
#include "blocks.cpp"

using namespace std;

class Game
{
public:
    Game();
    ~Game();

    bool gameOver;
    int score;

    void Draw();
    void HandleInput();
    void MoveBlockDown(); // TODO MAKE A GRAVITY

    Music music;

private:
    Grid grid;
    void Reset();

    // Movement
    void MoveBlockLeft();
    void MoveBlockRight();
    void HardDrop();

    // Rotation
    void RotateBlockCW();
    void RotateBlockCCW();
    void RotateBlock180();

    // Block selection
    Block currentBlock;
    vector<Block> nextBlocks;

    vector<Block> blocks;
    vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    void LockBlock();

    // Checks
    bool IsBlockOutside();
    bool BlockFits();

    // Other
    void UpdateScore(int linesCleared, int moveDownPoints);

    // Sounds
    Sound rotateSound;
    Sound clearSound;
};
