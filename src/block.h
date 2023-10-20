#pragma once
#include <vector>
#include <map>
#include "position.h"

using namespace std;

class Block
{
public:
    Block();
    int id;
    map<int, vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
}
