#pragma once
#include <vector>
#include <map>
#include "position.h"

class Block
{
public:
    Block();
    int id;
    void Initialize();
    void Print();
    void Draw();
    int grid[20][10];

private:
}
