#include "raylib.h"
#include "main.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_BULLETS 10

const int screenWidth = 1024;
const int screenHeight = 768;

int main() {

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

    // Array of bullets in the game.
    Bullet *bullets = instantiateBullets();


    float rotation = 0.0F;

    // The Main Game Loop.
    while (!WindowShouldClose()) {

        // Work out the rotation of the player.
        float yDifference = GetMouseY() - player.y;
        float xDifference = GetMouseX() - player.x;

        rotation = (atan2(-xDifference, yDifference) / (2 * PI)) * 360;       

        if (IsKeyDown(KEY_D)) player.x += 2.0f;
        if (IsKeyDown(KEY_A)) player.x -= 2.0f;
        if (IsKeyDown(KEY_W)) player.y -= 2.0f;
        if (IsKeyDown(KEY_S)) player.y += 2.0f;

        if (IsKeyReleased(KEY_SPACE)) {
            // Convert the rotation to radians.
            fire(bullets, player.x, player.y, (rotation / 360) * 2 * PI);
        }

        updateBullets(bullets);

        BeginDrawing();

            ClearBackground(RAYWHITE);


            DrawTexturePro(main_player, sourceRec, player, origin, rotation, WHITE);

            drawBullets(bullets);

        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


Bullet *instantiateBullets() {
    // Instantiate an array of bullets to be used for firing.
    Bullet *bullets = (Bullet*) malloc(sizeof(Bullet) * MAX_BULLETS);

    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet bullet;
        Vector2 position = {0, 0};
        float size = 5;
        bullet.position = position;
        bullet.velocity = 20;
        bullet.isActive = false;
        bullet.size = size;
        bullet.angle = 0;
        bullets[i] = bullet;
    }

    return bullets;
}


// Triggered when the user presses the mouse.
void fire(Bullet *bullets, float playerPosX, float playerPosY, float angle) {

    // Iterate over the bullets and find one which is not active.
    Bullet *bullet = NULL;

    // Remembering to get the memory address of the bullet.
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            bullet = &bullets[i];
        }
    }

    if (bullet != NULL) {
        bullet -> isActive = true;
        bullet -> position.x = playerPosX;
        bullet -> position.y = playerPosY;
        bullet -> angle = angle;
    }
}

// Draw the bullets
void drawBullets(Bullet *bullets) {

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            DrawCircleV(bullets[i].position, bullets[i].size, RED);
        }
    }
}

// Update the position of the bullets
void updateBullets(Bullet *bullets) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            // Update the position of the bullet.
            bullets[i].position.x += bullets[i].velocity * -sinf(bullets[i].angle);
            bullets[i].position.y += bullets[i].velocity * cosf(bullets[i].angle);

            // Check if it has gone out of the screen.

            if (bullets[i].position.x > screenWidth || bullets[i].position.x < 0 
                                    || bullets[i].position.y > screenHeight || bullets[i].position.y < 0) {
                bullets[i].isActive = false;
            } 
        }
    }
}