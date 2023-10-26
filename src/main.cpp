#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime > interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    Color darkBlue = {44, 44, 127, 255};

    InitWindow(1000, 620, "ComputeTris");
    SetTargetFPS(60);

    Font font = LoadFontEx("src/fonts/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);

        game.HandleInput();

        // Gravity
        // if (EventTriggered(0.5))
        //     game.MoveBlockDown();

        BeginDrawing();
        ClearBackground(darkBlue);

        // Draw score
        // char scoreText[10];
        // sprintf(scoreText, "%d", game.score);
        // Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        // DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        // DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        // DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

        // Draw next queue
        // DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        // DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        // Game over text
        // if (game.gameOver)
        //     DrawTextEx(font, "GAME OVER", {320, 450}, 32, 2, WHITE);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}
