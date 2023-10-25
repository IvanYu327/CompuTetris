#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main()
{
    InitWindow(300, 600, "CompuTetris");
    SetTargetFPS(60);

    Color darkBlue = {44, 44, 127, 255};

    Grid grid = Grid();
    grid.Print();

    TBlock block = TBlock();
    block.Move(4, 3);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        grid.Draw();

        block.Draw();

        EndDrawing();
    }

    CloseWindow();
}
