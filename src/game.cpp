#include "game.h"
#include <random>

using namespace std;

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();

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
    currentBlock.Move(0, -1);
    if (IsBlockOutside())
        currentBlock.Move(0, 1);
}

void Game::MoveBlockRight()
{
    currentBlock.Move(0, 1);
    if (IsBlockOutside())
        currentBlock.Move(0, -1);
}

void Game::MoveBlockDown()
{
    currentBlock.Move(1, 0);
    if (IsBlockOutside())
        currentBlock.Move(-1, 0);
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

void Game::RotateBlockCW()
{
    currentBlock.RotateCW();
    if (IsBlockOutside())
        currentBlock.RotateCCW();
}

void Game::RotateBlockCCW()
{
    currentBlock.RotateCCW();
    if (IsBlockOutside())
        currentBlock.RotateCW();
}

void Game::RotateBlock180()
{
    currentBlock.Rotate180();
    if (IsBlockOutside())
        currentBlock.Rotate180();
}
