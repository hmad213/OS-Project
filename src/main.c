#include "../include/main.h"
 
int main(void)
{
    int stage = 0;

    Pipeline pipeline;
    pipelineInit(&pipeline);
 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib project");
    SetTargetFPS(100);

    int pipelineStarted = 0;
    double pipelineStart;
    int processingFinished = 0;

    Font font = LoadFont("./assets/Roboto.ttf");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if(stage == 3 && !pipelineStarted){
            runPipeline(&pipeline);
            pipelineStart = GetTime();
            pipelineStarted = 1;
        }

        if(pipelineStarted && !processingFinished){
            if(pipeline.savedCount >= pipeline.batch.index){
                double totalTime = GetTime() - pipelineStart;
                processingFinished = 1;
                printf("PIPELINING BENCHMARK\n");
                printf("Image processed: %d\n", pipeline.savedCount);
                printf("Total time taken: %.4f seconds\n", totalTime);
            }
        }

        if(stage == 0){
            drawSelectorStage(pipeline.batch.paths, &pipeline.batch.index, pipeline.batch.count, font, &stage);
        }else if(stage == 1){
            drawEnhancerStage(font, &pipeline.enhancerName, &stage);
        }else if(stage == 2){
            drawFilterStage(font, &pipeline.filterName, &stage);
        }else if(stage == 3){
            drawProgressStage(&pipeline);
        }

        EndDrawing();
    }
 
    CloseWindow();

    pipelineDestroy(&pipeline);
    return 0;
}
