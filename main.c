#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_BULLETS 10

typedef struct {
    Vector2 position;
    float velocity;
    bool isActive;
} Bullet;

int main() {

    const int screenWidth = 1024;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Tim's Game In C");

    SetTargetFPS(60);

    float xPos = screenWidth / 2;
    float yPos = screenHeight / 2;

    Texture2D main_player = LoadTexture("img/player.png");

    // What part of the texture we will use to draw the player.
    Rectangle sourceRec = { 0.0f, 0.0f, main_player.width, main_player.height};

    // Define the point in the world where the texture is to be displayed.
    // I could scale it if I wanted to.
    Rectangle player = {xPos, yPos, main_player.width, main_player.height};    

    // Origin of the texture relative to the destination rectangle.
    // Point of the texture used as reference for rotation and scaling.
    Vector2 origin = {main_player.width / 2, main_player.height / 2};

    float rotation = 0.0F;

    // The Main Game Loop.
    while (!WindowShouldClose()) {

        // Work out the rotation of the player.
        float yDifference = GetMouseY() - player.y;
        float xDifference = GetMouseX() - player.x;


        rotation = (atan2(-xDifference, yDifference) / (2 * PI)) * 360;       

        if (IsKeyDown(KEY_RIGHT)) player.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) player.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) player.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) player.y += 2.0f;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexturePro(main_player, sourceRec, player, origin, rotation, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

Bullet *instantiateBullets() {
    
}