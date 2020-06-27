#include "raylib.h"
#include "main.h"
#include "enemy.c"
#include "player.c"
#include "environment.c"
#include "camera.c"

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

    Dust *dust = instantiateDust();

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

    Rectangle worldRect = (Rectangle) {1000, 1000, worldWidth - 1000, 
                                                    worldHeight - 1000};

    CamStruct camera = instantiateCamera(worldWidth / 2, worldHeight / 2);

    // True if the game has started.
    bool start = false;
    int games = 0;

    // Time since the user pressed P.
    float timeStarted = 0;
    float timeDied = 0;

    InitAudioDevice();

    // Sound effects in the game.
    Sound hitSound = LoadSound("efx/hit.wav");
    Sound shootSound = LoadSound("efx/shoot.wav");
    Sound explosionSound = LoadSound("efx/explosion.wav");
    Sound playerDeadSound = LoadSound("efx/player_dead.wav");

    // The main game loop.
    while (!WindowShouldClose()) {
            
                     

        if (IsKeyReleased(KEY_SPACE)) {
            // Convert the rotation to radians.
            if (player.isAlive)
                fireNormal(bullets, player.boundingBox.x, player.boundingBox.y, 
                                            (player.rotation / 360) * 2 * PI,
                                            shootSound);
        }

        if (IsKeyReleased(KEY_Z)) 
            if (player.isAlive)
                fireScatter(bullets, player.boundingBox.x, 
                                            player.boundingBox.y, 
                                            explosionSound);

        if (playerInBounds(player.boundingBox, worldRect))
            updateCamera(&camera, player, dust, stars, elapsedTime);

        if (!start && IsKeyReleased(KEY_P)) {
            start = true;
            timeStarted = GetTime();
        }

        updateBullets(bullets, elapsedTime);
        updateEnemies(enemies, player, elapsedTime);
        killEnemies(enemies, bullets, hitSound);

        movePlayer(&player, elapsedTime, camera.cam, dust, stars, worldRect);

        if (start){
            if ((GetTime() - timeLastSpawn) > 4){
                for (int i = 0; i < spawnAmount; i++)
                    spawnEnemy(enemies);
                timeLastSpawn = GetTime();
            }

            if (GetTime() - lastChange > 10) {
                spawnAmount++;
                lastChange = GetTime();
            } 

            if (isPlayerDead(enemies, player)) {
                player.isAlive = false;
                start = false;
                games++;
                timeDied = GetTime();
                reset(enemies, &player, &camera);
                PlaySound(playerDeadSound);
                spawnAmount = 1;
                
            }
        }

        BeginDrawing();

            ClearBackground(BLACK);
            
            BeginMode2D(camera.cam);

                drawStars(stars);

                drawBullets(bullets);

                if (player.isAlive)
                    DrawPoly((Vector2) {player.boundingBox.x, player.boundingBox.y}, 
                                            3, player.size, player.rotation,
                                            (Color) {255, 0, 0, 200});

    
                drawEnemies(enemies, player);

            drawDust(dust);

            EndMode2D();

            

            // If the game has not started then draw the start screen.
            if (!start) {

                char *msg = "Press P to Start";
                
                // Work out the size of the text.
                int width = MeasureText(msg, 20);

                DrawText(FormatText(msg), screenWidth/2 - width/2, 
                                        50, 20, WHITE);

                if (games > 0) {
                    const char *diedMsg = FormatText("You lasted %.2f seconds", 
                                                                    timeDied);
                    int diedWidth = MeasureText(diedMsg, 20);
                    DrawText(diedMsg, screenWidth/2 - diedWidth/2, screenHeight/2,
                                                                20, WHITE);

                }
            } else {                
                DrawText(FormatText("Time: %.2f", GetTime() - timeStarted), 
                                                        10, 10, 20, WHITE);
            }

        EndDrawing();      

        elapsedTime = GetFrameTime(); 
    }

    freeDataStructs(enemies, bullets, stars, dust);
    UnloadSound(hitSound);
    UnloadSound(shootSound);
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
void freeDataStructs(Enemy *enemies, Bullet *bullets, Star *stars, Dust *dust) {
    free(enemies);
    free(bullets);
    free(stars);
    free(dust);
}

/**
 * @brief Resets the game back to the start. 
 * 
 * @param enemies the array of enemies in the game.
 * @param player a pointer to the player so that we can change the 
 * position of the player.
 */
void reset(Enemy *enemies,  Player *player, CamStruct *camera) {
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].isAlive = false;
    }

    player -> boundingBox.x = worldWidth / 2;
    player -> boundingBox.y = worldWidth / 2;
    player -> isAlive = true;

    camera -> cam.target.x = player -> boundingBox.x;
    camera -> cam.target.y = player -> boundingBox.y;

}





