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
    void Move(int rows, int columns);
    vector<Position> GetCellPositions();
    void RotateCW();
    void RotateCCW();
    void Rotate180();
    void Rotate();
    int id;
    map<int, vector<Position>> cells;

private:
    // Size params
    int cellSize;
    int drawXOffset;
    int drawYOffset;

    int rotationState;
    vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
