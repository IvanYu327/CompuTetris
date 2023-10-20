#include <raylib.h>
#include "grid.h"

int main()
{
    InitWindow(300, 600, "CompuTetris");
    SetTargetFPS(60);

    Color darkBlue = {44, 44, 127, 255};

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[3][5] = 4;
    grid.grid[9][9] = 7;
    grid.Print();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        grid.Draw();

        EndDrawing();
    }

    CloseWindow();
}
