#include "../include/main.h"
 
int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;
 
    InitWindow(screenWidth, screenHeight, "raylib project");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("It works!", 320, 200, 30, DARKGRAY);
        EndDrawing();
    }
 
    CloseWindow();
    return 0;
}
