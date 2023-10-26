#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include "constants.h"

using namespace std;
using namespace CONSTANTS;

class Block
{
public:
    Block();
    void Draw(int offsetX = DRAW_GRID_X_OFFSET, int offsetY = DRAW_GRID_Y_OFFSET);

    // Move and rotate
    void Move(int rows, int columns);
    void Reset();
    vector<Position> GetCellPositions();
    void RotateWithKick(int times, int rowOffset = 0, int columnOffset = 0);

    // Properties
    int id;
    int rotationState;
    map<int, vector<Position>> cells;

private:
    // Size params
    int cellSize;
    int drawXOffset;
    int drawYOffset;

    vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
