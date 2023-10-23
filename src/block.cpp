#include "block.h"
#include <vector>

using namespace std;

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw()
{
    vector<Position> tiles = cells[rotationState];
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + 1, item.row * cellSize + 1, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

vector<Position> Block::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
}
