#include "raylib.h"
#include "main.h"
#include "enemy.c"
#include "player.c"

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Where the game is run. 
 * Contains variables to do with the state of the game.
 * 
 * @return int returns 0 if success.
 */
int main() {

    // Initialise the game window.
    InitWindow(screenWidth, screenHeight, "Square Survival");

    SetTargetFPS(60);

    // An array of all the bullets in the game.
    Bullet *bullets = instantiateBullets();

    // The main player.
    Player player = instantiatePlayer();

    // An array of all enemies. (We recycle eneies)
    Enemy *enemies = instantiateEnemies();

    /*  Keeps track of when enemies
        last spawned in the game. */
    int timeLastSpawn = 0;

    /* Keeps track of the last spawn change/ */
    double lastChange = 0;

    // The number of enemies to spawn per 'round.
    int spawnAmount = 1;

    // The main game loop.
    while (!WindowShouldClose()) {
        
        movePlayer(&player);             

        if (IsKeyReleased(KEY_SPACE)) {
            // Convert the rotation to radians.
            if (player.isAlive)
                fire(bullets, player.boundingBox.x, player.boundingBox.y, 
                                            (player.rotation / 360) * 2 * PI);
        }

        if (IsKeyPressed(KEY_R)) reset(enemies, &player);

        updateBullets(bullets);
        updateEnemies(enemies, player);
        killEnemies(enemies, bullets);

        if ((GetTime() - timeLastSpawn) > 4){
            for (int i = 0; i < spawnAmount; i++)
                spawnEnemy(enemies);
            timeLastSpawn = GetTime();
        }

        if (GetTime() - lastChange > 10) {
            spawnAmount++;
            lastChange = GetTime();
        } 

        if (isPlayerDead(enemies, player))
            player.isAlive = false;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            if (player.isAlive)
                DrawRectanglePro(player.boundingBox, player.origin,
                                                         player.rotation, RED);          
            drawBullets(bullets); 
            drawEnemies(enemies, player);

        EndDrawing();       
    }

    freeDataStructs(enemies, bullets);
    CloseWindow();
    return 0;
}

void freeDataStructs(Enemy *enemies, Bullet *bullets) {
    free(enemies);
    free(bullets);
}


