#include "game.h"
#include <random>

using namespace std;

Game::Game()
{
    grid = Grid();

    blocks = GetAllBlocks();

    gameOver = false;
    score = 0;

    currentBlock = LBlock(); // GetRandomBlock();
    for (int i = 0; i < 5; i++)
        nextBlocks.emplace_back(GetRandomBlock());
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
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), ZBlock(), TBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if (gameOver && keyPressed == KEY_R)
        Reset();

    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;

    case KEY_RIGHT:
        MoveBlockRight();
        break;

    case KEY_DOWN:
        MoveBlockDown();
        break;

    case KEY_UP:
        RotateBlockCW();
        break;

    case KEY_X:
        RotateBlockCCW();
        break;

    case KEY_Z:
        RotateBlock180();
        break;

    default:
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (gameOver)
        return;

    currentBlock.Move(0, -1);
    if (IsBlockOutside() || !BlockFits())
        currentBlock.Move(0, 1);
}

void Game::MoveBlockRight()
{
    if (gameOver)
        return;

    currentBlock.Move(0, 1);
    if (IsBlockOutside() || !BlockFits())
        currentBlock.Move(0, -1);
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

void Game::RotateBlockCW()
{
    if (gameOver)
        return;

    currentBlock.RotateCW();
    if (IsBlockOutside() || !BlockFits())
        currentBlock.RotateCCW();
}

void Game::RotateBlockCCW()
{
    if (gameOver)
        return;

    currentBlock.RotateCCW();
    if (IsBlockOutside() || !BlockFits())
        currentBlock.RotateCW();
}

void Game::RotateBlock180()
{
    if (gameOver)
        return;

    currentBlock.Rotate180();
    if (IsBlockOutside() || !BlockFits())
        currentBlock.Rotate180();
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }

    currentBlock = nextBlocks[0];
    if (!BlockFits())
        gameOver = true;

    nextBlocks.erase(nextBlocks.begin());
    nextBlocks.emplace_back(GetRandomBlock());

    int rowsCleared = grid.ClearFullRows();
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
            return true;
    }
    return false;
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (!grid.IsCellEmpty(item.row, item.column))
            return false;
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    gameOver = false;
    for (int i = 0; i < 5; i++)
        nextBlocks.emplace_back(GetRandomBlock());
    score = 0;
}
