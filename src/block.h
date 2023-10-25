#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

using namespace std;

class Block
{
public:
    Block();
    void Draw();
    void Move(int rows, int columns);
    vector<Position> GetCellPositions();
    void RotateCW();
    void RotateCCW();
    void Rotate180();
    int id;
    map<int, vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
