#include "../include/renderer.h"

char error[100];

void drawSelector(char** pathArray, int* count, int maxCount, Font font, int* stage) {
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
            char buffer[4096];
            if (fgets(buffer, sizeof(buffer), fp)) {
                buffer[strcspn(buffer, "\n")] = 0;
                char *token = strtok(buffer, "|");
                while (token && *count < maxCount) {
                    if (IsFileExtension(token, ".png")  || IsFileExtension(token, ".bmp") || 
                        IsFileExtension(token, ".tga")  || IsFileExtension(token, ".jpg") || 
                        IsFileExtension(token, ".jpeg") || IsFileExtension(token, ".gif") || 
                        IsFileExtension(token, ".qoi")  || IsFileExtension(token, ".psd"))
                    {
                        pathArray[*count] = strdup(token);
                        (*count)++;
                        strcpy(error, "");
                    }else{
                        strcpy(error, "Error: File format must be one of the following [png, jpg, jpeg, bmp, tga, gif, qoi, psd]!");
                    }
                    token = strtok(NULL, "|");
                }
            }
            pclose(fp);
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), btnLoad) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && *count > 0){
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