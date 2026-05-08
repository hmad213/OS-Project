#include "../include/renderer.h"

char error[100];

void drawSelectorStage(char** pathArray, int* count, int maxCount, Font font, int* stage) {
    const float btnW = 200;
    const float btnH = 60;
    const float spacing = 40;
    
    float totalWidth = (btnW * 2) + spacing;
    float startX = (SCREEN_WIDTH / 2.0f) - (totalWidth / 2.0f);
    float centerY = (SCREEN_HEIGHT / 2.0f);

    Rectangle btnLoad = { startX, centerY + 100.0f, btnW, btnH };
    Rectangle btnNext = { startX + btnW + spacing, centerY + 100.0f, btnW, btnH };

    if (CheckCollisionPointRec(GetMousePosition(), btnLoad) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        FILE *fp = popen("zenity --file-selection --multiple --separator='|' --title='Select Images'", "r");
        if (fp) {
            char buffer[4096] = {0};
            // Read entire output, not just first line
            size_t total = 0;
            while (total < sizeof(buffer) - 1) {
                size_t n = fread(buffer + total, 1, sizeof(buffer) - 1 - total, fp);
                if (n == 0) break;
                total += n;
            }
            buffer[total] = 0;
            buffer[strcspn(buffer, "\n")] = 0; // strip trailing newline

            printf("raw: '%s'\n", buffer); // debug: see exactly what zenity returned

            char *token = strtok(buffer, "|");
            while (token && *count < maxCount) {
                // strip any leading/trailing whitespace from token
                while (*token == ' ') token++;
                char *end = token + strlen(token) - 1;
                while (end > token && *end == ' ') *end-- = 0;

                if (IsFileExtension(token, ".png")  || IsFileExtension(token, ".bmp") ||
                    IsFileExtension(token, ".jpg")  || IsFileExtension(token, ".jpeg"))
                {
                    pathArray[*count] = strdup(token);
                    printf("path[%d]: '%s'\n", *count, pathArray[*count]);
                    (*count)++;
                    strcpy(error, "");
                } else {
                    strcpy(error, "Error: File format must be one of the following [png, jpg, jpeg, bmp]!");
                }
                token = strtok(NULL, "|");
            }
            pclose(fp);
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), btnNext) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *count > 0){
        (*stage) = 1;
        strcpy(error, "");
    }

    char imgText[150];
    sprintf(imgText, "%d images selected!", *count);
    Vector2 imgTextSize = MeasureTextEx(font, imgText, 30, 2.0f);
    Vector2 errorTextSize = MeasureTextEx(font, error, 24, 2.0f);

    BeginDrawing();
        ClearBackground((Color){60, 60, 60, 255});
        DrawTextEx(font, imgText, (Vector2){(SCREEN_WIDTH / 2.0f) - (imgTextSize.x / 2.0f), centerY}, 30, 2.0f, GREEN);
        if(strlen(error) != 0){
            DrawTextEx(font, error, (Vector2){(SCREEN_WIDTH / 2.0f) - (errorTextSize.x / 2.0f), centerY + 50}, 24, 2.0f, RED);
        }
        drawButton(btnLoad, "LOAD", RED);
        if(*count == 0) drawButton(btnNext, "NEXT", DARKGRAY);
        else drawButton(btnNext, "NEXT", RED);
    EndDrawing();
}

void drawButton(Rectangle bounds, const char* text, Color color) {
    const int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    
    DrawRectangleRounded(bounds, 0.3f, 10, color);
    DrawText(text, 
             bounds.x + (bounds.width / 2.0f) - (textWidth / 2.0f), 
             bounds.y + (bounds.height / 2.0f) - (fontSize / 2.0f), 
             20, WHITE);
}

void drawEnhancerStage(Font font, char** enhancer, int* stage){
    const char* enhancers[] = {
        WARMTH, BRIGHTEN, CONTRAST, SHARPEN, SATURATE
    };

    char* selectorText = "Please select an Enhancer: ";
    Vector2 imgTextSize = MeasureTextEx(font, selectorText, 30, 2.0f);

    float btnW = 180.0f;
    float btnH = 50.0f;
    float hSpacing = 20.0f;
    float vSpacing = 20.0f;
    float startY = 250.0f;

    float row1Width = (3 * btnW) + (2 * hSpacing);
    float row2Width = (2 * btnW) + (1 * hSpacing);

    float startX1 = (GetScreenWidth() - row1Width) / 2.0f;
    float startX2 = (GetScreenWidth() - row2Width) / 2.0f;

    Vector2 mousePos = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    float startX = (SCREEN_WIDTH / 2.0f) - (200 / 2.0f);
    float centerY = (SCREEN_HEIGHT / 2.0f);
    Rectangle btnNext = {(SCREEN_WIDTH / 2.0f) - (200 / 2.0f), (SCREEN_HEIGHT / 2.0f) + 100.0f, 200, 60};

    if(clicked && CheckCollisionPointRec(mousePos, btnNext)){
        (*stage) = (*stage) + 1;
    }

    BeginDrawing();
        ClearBackground((Color){60, 60, 60, 255});
        DrawTextEx(font, selectorText, (Vector2){(SCREEN_WIDTH / 2) - (imgTextSize.x / 2), 150}, 30, 2.0f, GREEN);

        for (int i = 0; i < 3; i++) {
            Rectangle bounds = { 
                startX1 + (i * (btnW + hSpacing)), 
                startY, 
                btnW, 
                btnH 
            };
            if(strcmp(*enhancer, enhancers[i]) == 0){
                drawButton(bounds, enhancers[i], GREEN);
            }
            else if (CheckCollisionPointRec(mousePos, bounds)) {
                if (clicked) *enhancer = enhancers[i];
                drawButton(bounds, enhancers[i], GRAY);
            } else {
                drawButton(bounds, enhancers[i], DARKGRAY);
            }
        }

        for (int i = 0; i < 2; i++) {
            Rectangle bounds = { 
                startX2 + (i * (btnW + hSpacing)), 
                startY + btnH + vSpacing, 
                btnW, 
                btnH 
            };
            if(strcmp(*enhancer, enhancers[i + 3]) == 0){
                drawButton(bounds, enhancers[i + 3], GREEN);
            }
            else if (CheckCollisionPointRec(mousePos, bounds)) {
                if (clicked) *enhancer = enhancers[i + 3];
                drawButton(bounds, enhancers[i + 3], GRAY);
            } else {
                drawButton(bounds, enhancers[i + 3], DARKGRAY);
            }
        }

        if(strlen(*enhancer) == 0) drawButton(btnNext, "NEXT", DARKGRAY);
        else if(CheckCollisionPointRec(mousePos, btnNext)) drawButton(btnNext, "NEXT", MAROON);
        else drawButton(btnNext, "NEXT", RED);
    EndDrawing();
}

void drawProgressStage(Pipeline* p){
    BeginDrawing();
        ClearBackground((Color){60, 60, 60, 255});
        DrawText("Progress", 100, 100, 10, BLACK);
    EndDrawing();
}

void drawFinishStage(){
    BeginDrawing();
        ClearBackground((Color){60, 60, 60, 255});
        DrawText("Progress", 100, 100, 10, BLACK);
    EndDrawing();
}