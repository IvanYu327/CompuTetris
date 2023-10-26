#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "rotationSystem.h"

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

    // Configs
    const float ARR_DELAY = 0.0f;   // Auto-Repeat Rate delay in seconds
    const float DAS_DELAY = 0.110f; // Delayed Auto-Shift delay in seconds

    // Movement flags
    float dasTimer = 0.0f; // Delayed Auto-Shift timer
    float arrTimer = 0.0f; // Auto-Repeat Rate timer
    bool moveLeft = false;
    bool moveRight = false;

    // Movement
    void MoveBlockLeft(int count = 1);
    void MoveBlockRight(int count = 1);
    void HardDrop();
    void SoftDrop();

    // Rotation
    void RotateBlock(int times);
    RotationSystem rotationSystem;

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
