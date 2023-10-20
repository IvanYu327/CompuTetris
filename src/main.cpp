#include <raylib.h>
#include "grid.h"

int main()
{
    InitWindow(300, 600, "CompuTetris");
    SetTargetFPS(60);

    Color darkBlue = {44, 44, 127, 255};

    Grid grid = Grid();
    grid.Print();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);

        EndDrawing();
    }

    CloseWindow();
}
