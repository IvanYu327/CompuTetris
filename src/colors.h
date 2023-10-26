#pragma once
#include <raylib.h>
#include <vector>

using namespace std;

extern const Color darkGrey;

// Block colors
extern const Color green;  // S
extern const Color red;    // Z
extern const Color orange; // L
extern const Color yellow; // O
extern const Color purple; // T
extern const Color cyan;   // I
extern const Color blue;   // J

// Other colors
extern const Color lightBlue;
extern const Color darkBlue;

vector<Color> GetCellColors();
