#include "block.h"
#include <vector>
#include "constants.h"
#include <iostream>

using namespace std;
using namespace CONSTANTS;

Block::Block()
{
    cellSize = CELL_SIZE;
    drawXOffset = DRAW_GRID_X_OFFSET;
    drawYOffset = DRAW_GRID_Y_OFFSET;

    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX + 1, item.row * cellSize + offsetY + 1, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

void Block::Reset()
{
    rowOffset = 0;
    columnOffset = 0;
    rotationState = 0;

    switch (id)
    {
    case 1:
        Move(-1, 3);
        break;
    case 4:
        Move(0, 4);
        break;
    default:
        Move(0, 3);
        break;
    }
}

vector<Position> Block::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;

    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::RotateWithKick(int times, int rowOffset, int columnOffset)
{
    // cout
    //     << rotationState << ">>" << (rotationState + times) % cells.size() << " " << columnOffset << " " << rowOffset << endl;
    rotationState = (rotationState + times) % cells.size();
    Move(rowOffset, columnOffset);
}
