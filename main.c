#include "raylib.h"
#include "main.h"
#include "enemy.c"
#include "player.c"
#include "environment.c"

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

    // Instantiate the stars to user
    Star *stars = instantiateStars();

    /*  Keeps track of when enemies
        last spawned in the game. */
    int timeLastSpawn = 0;

    /* Keeps track of the last spawn change/ */
    double lastChange = 0;

    // The number of enemies to spawn per 'round.
    int spawnAmount = 1;

    /* Elapsed time used to ensure everything moves at the same speed regardless
       of the frame rate. */
    
    float elapsedTime = 0;

    // The main game loop.
    while (!WindowShouldClose()) {
        
                     

        if (IsKeyReleased(KEY_SPACE)) {
            // Convert the rotation to radians.
            if (player.isAlive)
                fireNormal(bullets, player.boundingBox.x, player.boundingBox.y, 
                                            (player.rotation / 360) * 2 * PI);
        }

        if (IsKeyReleased(KEY_Z)) 
            if (player.isAlive)
                fireScatter(bullets, player.boundingBox.x, 
                                                        player.boundingBox.y);

        if (IsKeyPressed(KEY_R)) reset(enemies, &player);

        updateBullets(bullets, elapsedTime);
        updateEnemies(enemies, player, elapsedTime);
        killEnemies(enemies, bullets);
        movePlayer(&player, elapsedTime);

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

            ClearBackground(BLACK);

            drawStars(stars);

            if (player.isAlive)
                DrawRectanglePro(player.boundingBox, player.origin,
                                                         player.rotation, RED);          
            drawBullets(bullets); 
            drawEnemies(enemies, player);

            DrawFPS(10, 10);

        EndDrawing();      

        elapsedTime = GetFrameTime(); 
    }

    freeDataStructs(enemies, bullets);
    CloseWindow();
    return 0;
}

/**
 * @brief Frees the memory allocation for the enemies and bullets
 * arrrays.
 * 
 * @param enemies The array of enemies.
 * @param bullets The array of bullets.
 */
void freeDataStructs(Enemy *enemies, Bullet *bullets) {
    free(enemies);
    free(bullets);
}

/**
 * @brief Resets the game back to the start. 
 * 
 * @param enemies the array of enemies in the game.
 * @param player a pointer to the player so that we can change the 
 * position of the player.
 */
void reset(Enemy *enemies,  Player *player) {
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].isAlive = false;
    }

    player -> boundingBox.x = screenWidth / 2;
    player -> boundingBox.y = screenHeight / 2;
    player -> isAlive = true;
}





