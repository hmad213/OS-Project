#include "../include/main.h"
 
int main(void)
{
    int stage = 0;

    Pipeline pipeline;
    pipelineInit(&pipeline);
 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib project");
    SetTargetFPS(100);

    int pipelineStarted = 0;

    Font font = LoadFont("./assets/Roboto.ttf");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if(stage == 1 && !pipelineStarted){
            runPipeline(&pipeline);
            pipelineStarted = 1;
        }

        if(stage == 0){
            drawSelectorStage(pipeline.batch.paths, &pipeline.batch.index, pipeline.batch.count, font, &stage);
        }else if(stage == 1){
            drawEnhancerStage(font, &pipeline.enhancerName, &stage);
        }else if(stage == 2){
            drawFinishStage(&pipeline);
        }

        if(pipeline.saverCount > pipeline.batch.count){
            stage == 2;
        }

        EndDrawing();
    }
 
    CloseWindow();

    pipelineDestroy(&pipeline);
    return 0;
}
