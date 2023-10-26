#include "grid.h"
#include <iostream>
#include "colors.h"
#include "constants.h"

using namespace std;
using namespace CONSTANTS;

Grid::Grid()
{
    cellSize = CELL_SIZE;
    drawXOffset = DRAW_GRID_X_OFFSET;
    drawYOffset = DRAW_GRID_Y_OFFSET;

    numRows = 20;
    numCols = 10;

    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
        for (int column = 0; column < numCols; column++)
            grid[row][column] = 0;
}

void Grid::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
            cout << grid[row][column] << " ";
        cout << endl;
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = grid[row][column];
            Color cellColor = colors[cellValue];
            DrawRectangle(column * cellSize + drawXOffset + 1, row * cellSize + drawYOffset + 1, cellSize - 1, cellSize - 1, cellColor);
        }
}

bool Grid::IsCellOutside(int row, int column)
{
    return row < 0 || row >= numRows || column < 0 || column >= numCols;
}

bool Grid::IsCellEmpty(int row, int column)
{
    return grid[row][column] == 0;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        if (grid[row][column] == 0)
            return false;
    }
    return true;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
            MoveRowDown(row, completed);
    }
    return completed;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++)
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
