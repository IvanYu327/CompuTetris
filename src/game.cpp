#include "game.h"
#include <random>
#include <cmath>
#include <iostream>

using namespace std;

Game::Game()
{
    grid = Grid();

    blocks = GetAllBlocks();
    rotationSystem = RotationSystem();

    gameOver = false;
    score = 0;

    // Init movement flags
    dasTimer = 0.0f;
    arrTimer = 0.0f;
    softDropTimer = 0.0f;
    moveLeft = false;
    moveRight = false;
    held = false;

    currentBlock = GetRandomBlock();
    holdBlock = nullptr;
    for (int i = 0; i < 5; i++)
        nextBlocks.emplace_back(GetRandomBlock());

    // Load music and sounds
    InitAudioDevice();
    music = LoadMusicStream("src/sounds/music.mp3");
    // PlayMusicStream(music);
    rotateSound = LoadSound("src/sounds/rotate.mp3");
    clearSound = LoadSound("src/sounds/clear.mp3");
}

Game::~Game()
{
    delete holdBlock;
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
        blocks = GetAllBlocks();

    int index = rand() % blocks.size();
    Block block = blocks[index];
    blocks.erase(blocks.begin() + index);
    return block;
}

vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();

    if (!gameOver)
        currentBlock.Draw();

    Block nextBlock = nextBlocks[0];

    if (holdBlock != nullptr)
    {
        switch (holdBlock->id)
        {
        case 1:
            holdBlock->Draw(DRAW_GRID_X_OFFSET - CELL_SIZE * 7.5, DRAW_GRID_Y_OFFSET + CELL_SIZE * 2);
            break;
        case 4:
            holdBlock->Draw(DRAW_GRID_X_OFFSET - CELL_SIZE * 7, DRAW_GRID_Y_OFFSET + CELL_SIZE * 2);
            break;
        default:
            holdBlock->Draw(DRAW_GRID_X_OFFSET - CELL_SIZE * 6.5, DRAW_GRID_Y_OFFSET + CELL_SIZE * 2);
            break;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        Block nextBlock = nextBlocks[i];
        switch (nextBlock.id)
        {
        case 1:
            nextBlock.Draw(DRAW_GRID_X_OFFSET + CELL_SIZE * 7.5, CELL_SIZE * (i * 3 + 1));
            break;
        case 4:
            nextBlock.Draw(DRAW_GRID_X_OFFSET + CELL_SIZE * 7.5, CELL_SIZE * (i * 3 + 1));
            break;
        default:
            nextBlock.Draw(DRAW_GRID_X_OFFSET + CELL_SIZE * 8, CELL_SIZE * (i * 3 + 1));
            break;
        }
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if (keyPressed == KEY_SPACE)
        HardDrop();
    if (keyPressed == KEY_LEFT)
    {
        MoveBlockLeft();
        moveLeft = true;
        moveRight = false;
        dasTimer = 0.0f;
        arrTimer = 0.0f;
    }
    if (keyPressed == KEY_RIGHT)
    {
        MoveBlockRight();
        moveRight = true;
        moveLeft = false;
        dasTimer = 0.0f;
        arrTimer = 0.0f;
    }
    if (keyPressed == KEY_UP)
        RotateBlock(1); // CW
    if (keyPressed == KEY_X)
        RotateBlock(3); // CCW
    if (keyPressed == KEY_Z)
        RotateBlock(2); // 180

    if (keyPressed == KEY_R)
        Reset();
    if (keyPressed == KEY_DOWN)
        SoftDrop();
    if (keyPressed == KEY_C)
        Hold();

    // Check if a movement key is currently pressed
    bool movingLeft = IsKeyDown(KEY_LEFT) && moveLeft;
    bool movingRight = IsKeyDown(KEY_RIGHT) && moveRight;
    bool movingDown = IsKeyDown(KEY_DOWN);

    if (!movingLeft && !movingRight)
    {
        dasTimer = 0.0f;
        arrTimer = 0.0f;
    }

    // Handle left movement using DAS
    if (movingLeft)
    {
        // enter ARR
        if (dasTimer >= DAS_DELAY)
        {
            arrTimer += GetFrameTime();
            int timesToMove = floor(arrTimer / ARR_DELAY);

            if (ARR_DELAY == 0)
                MoveBlockLeft(10);
            else
                MoveBlockLeft(timesToMove);

            arrTimer -= timesToMove * ARR_DELAY;
        }
        // Increment DAS Delay
        else
        {
            dasTimer += GetFrameTime();
        }
    }

    // Handle right movement using DAS
    if (movingRight)
    {
        if (dasTimer >= DAS_DELAY)
        {
            arrTimer += GetFrameTime();

            int timesToMove = floor(arrTimer / ARR_DELAY);

            if (ARR_DELAY == 0)
                MoveBlockRight(10);
            else
                MoveBlockRight(timesToMove);

            arrTimer -= timesToMove * ARR_DELAY;
        }
        else
        {
            dasTimer += GetFrameTime();
        }
    }

    // Handle holding softdrop
    if (movingDown)
    {
        if (softDropTimer >= SOFT_DROP_DELAY)
        {
            softDropTimer += GetFrameTime();
            int timesToMove = floor(softDropTimer / SOFT_DROP_DELAY);

            if (SOFT_DROP_DELAY == 0)
                SoftDrop(99999);
            else
                SoftDrop(timesToMove);

            softDropTimer -= timesToMove * SOFT_DROP_DELAY;
        }
        else
            softDropTimer += GetFrameTime();
    }

    if (dasTimer > 0)
    {
        cout << "DAS: " << dasTimer << " ARR: " << arrTimer << endl;
    }
}

void Game::MoveBlockLeft(int count)
{
    if (gameOver)
        return;

    for (int i = 0; i < count; i++)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, 1);
            break;
        }
    }
}

void Game::MoveBlockRight(int count)
{
    if (gameOver)
        return;

    for (int i = 0; i < count; i++)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, -1);
            break;
        }
    }
}

void Game::MoveBlockDown()
{
    if (gameOver)
        return;

    currentBlock.Move(1, 0);
    if (IsBlockOutside() || !BlockFits())
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

void Game::SoftDrop(int count)
{
    if (gameOver)
        return;

    for (int i = 0; i < count; i++)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            // LockBlock();
            break;
        }
        else
            UpdateScore(0, 10);
    }
}

void Game::HardDrop()
{
    if (gameOver)
        return;

    int blocksMoved = 0;
    while (!IsBlockOutside() && BlockFits())
    {
        currentBlock.Move(1, 0);
        blocksMoved++;
    }

    blocksMoved--;
    currentBlock.Move(-1, 0);
    LockBlock();
    UpdateScore(0, blocksMoved * 10);
}

void Game::RotateBlock(int times)
{
    if (gameOver)
        return;

    // get rotation kick tests
    int endState = (currentBlock.rotationState + times) % currentBlock.cells.size();

    // cout << endl
    //      << "attempting rotation " << currentBlock.rotationState << ">>" << endState << " id " << currentBlock.id << endl;

    // get rotation kick tests
    vector<pair<int, int>> tests = rotationSystem.GetRotationTests(currentBlock.id, currentBlock.rotationState, endState);

    for (auto test : tests)
    {
        const int columnOffset = test.first;
        const int rowOffset = test.second;

        // cout << "trying test " << columnOffset << "  " << rowOffset << endl;
        currentBlock.RotateWithKick(times, rowOffset, columnOffset);
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.RotateWithKick(-times, -rowOffset, -columnOffset);
            // cout << "    failed" << endl;
        }
        else
        {
            // cout << "    success" << endl;
            PlaySound(rotateSound);
            return;
        }
    }
}

void Game::Hold()
{
    if (held)
        return;

    if (holdBlock == nullptr)
    {
        holdBlock = new Block(currentBlock); // Allocate and copy the currentBlock
        currentBlock = nextBlocks[0];
        nextBlocks.erase(nextBlocks.begin());
        nextBlocks.emplace_back(GetRandomBlock());
    }
    else
        swap(currentBlock, *holdBlock);

    held = true;
    holdBlock->Reset();
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();

    for (Position item : tiles)
        grid.grid[item.row][item.column] = currentBlock.id;

    currentBlock = nextBlocks[0];
    held = false;

    if (!BlockFits())
        gameOver = true;

    nextBlocks.erase(nextBlocks.begin());
    nextBlocks.emplace_back(GetRandomBlock());

    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
        if (grid.IsCellOutside(item.row, item.column))
            return true;

    return false;
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();

    for (Position item : tiles)
        if (!grid.IsCellEmpty(item.row, item.column))
            return false;

    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();

    if (holdBlock != nullptr)
    {
        delete holdBlock;
        holdBlock = nullptr;
    }

    gameOver = false;

    for (int i = 0; i < 5; i++)
        nextBlocks.emplace_back(GetRandomBlock());

    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    if (gameOver)
        return;

    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 1000;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}
