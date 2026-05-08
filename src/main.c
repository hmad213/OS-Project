#include "../include/main.h"
 
int main(void)
{
    int stage = 0;

    Pipeline pipeline;
    pipelineInit(&pipeline);
 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib project");
    SetTargetFPS(60);

    Font font = LoadFont("./assets/Roboto.ttf");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if(stage == 0){
            drawSelector(pipeline.batch.paths, &pipeline.batch.index, pipeline.batch.count, font, &stage);
        }

        EndDrawing();
    }
 
    CloseWindow();

    pipelineDestroy(&pipeline);
    return 0;
}
