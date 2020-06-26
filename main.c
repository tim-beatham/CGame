#include "raylib.h"
#include "main.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_BULLETS 10
#define MAX_ENEMIES 20

const int screenWidth = 1024;
const int screenHeight = 768;

int main() {

    InitWindow(screenWidth, screenHeight, "Tim's Game In C");

    SetTargetFPS(60);

    // Array of bullets in the game.
    Bullet *bullets = instantiateBullets();

    Player player = instantiatePlayer();

    Enemy *enemies = instantiateEnemies();

    int timeLastSpawn = 0;

    double lastChange = 0;

    int spawnAmount = 1;

    // The Main Game Loop.
    while (!WindowShouldClose()) {

        // Work out the rotation of the player.
        float yDifference = GetMouseY() - player.boundingBox.y;
        float xDifference = GetMouseX() - player.boundingBox.x;

        player.rotation = (atan2(-xDifference, yDifference) / (2 * PI)) * 360; 

        movePlayer(&player);             

        if (IsKeyReleased(KEY_SPACE)) {
            // Convert the rotation to radians.
            if (player.isAlive)
                fire(bullets, player.boundingBox.x, player.boundingBox.y, (player.rotation / 360) * 2 * PI);
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
                DrawRectanglePro(player.boundingBox, player.origin, player.rotation, RED);
            
            
            drawBullets(bullets); 
            drawEnemies(enemies, player);


        EndDrawing();

       
    }

    CloseWindow();
    return 0;
}

Player instantiatePlayer() {

    Player player;

    player.size = 50;
    player.boundingBox = (Rectangle) {screenWidth / 2, screenHeight / 2, player.size, player.size};
    player.rotation = 0;
    player.origin = (Vector2) {player.size/2, player.size/2};
    player.isAlive = true;
    player.velocity = 3.0f;

    return player;
}

void movePlayer(Player* player) {

    float xDirection = 0;
    float yDirection = 0;

    if (player -> isAlive){
        if (IsKeyDown(KEY_D)) xDirection += 1;
        if (IsKeyDown(KEY_A)) xDirection -= 1;
        if (IsKeyDown(KEY_W)) yDirection -= 1;
        if (IsKeyDown(KEY_S)) yDirection += 1;

        // Angle between the x and y.
        float resultant = sqrtf(pow(xDirection, 2) + pow(yDirection, 2));
        
        if (resultant != 0) {
            player -> boundingBox.x += ((player -> velocity) * (xDirection / resultant));
            player -> boundingBox.y += ((player -> velocity) * (yDirection / resultant));
        }
    }
}


Bullet *instantiateBullets() {
    // Instantiate an array of bullets to be used for firing.
    Bullet *bullets = (Bullet*) malloc(sizeof(Bullet) * MAX_BULLETS);

    for (int i = 0; i < MAX_BULLETS; i++) {
        float size = 10;
        Bullet bullet;
        Rectangle boundingBox = {0, 0, size, size};
        bullet.boundingBox = boundingBox;
        bullet.velocity = 5;
        bullet.isActive = false;
        bullet.size = size;
        bullet.angle = 0;
        bullet.origin = (Vector2) {bullet.size / 2, bullet.size / 2};
        bullets[i] = bullet;
    }

    return bullets;
}


void reset(Enemy *enemies,  Player *player) {
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].isAlive = false;
    }

    player -> boundingBox.x = screenWidth / 2;
    player -> boundingBox.y = screenHeight / 2;

    player -> isAlive = true;
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
        bullet -> boundingBox.x = playerPosX;
        bullet -> boundingBox.y = playerPosY;
        bullet -> angle = angle;
    }
}

// Draw the bullets
void drawBullets(Bullet *bullets) {

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            DrawRectanglePro(bullets[i].boundingBox, bullets[i].origin, 0, RED);
        }
    }
}

// Update the position of the bullets
void updateBullets(Bullet *bullets) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            // Update the position of the bullet.
            bullets[i].boundingBox.x += bullets[i].velocity * -sinf(bullets[i].angle);
            bullets[i].boundingBox.y += bullets[i].velocity * cosf(bullets[i].angle);

            // Check if it has gone out of the screen.

            if (bullets[i].boundingBox.x > screenWidth || bullets[i].boundingBox.x < 0 
                                    || bullets[i].boundingBox.y > screenHeight || bullets[i].boundingBox.y < 0) {
                bullets[i].isActive = false;
            } 
        }
    }
}

Enemy *instantiateEnemies() {
    Enemy *enemies = (Enemy*) malloc(sizeof(Enemy) * MAX_ENEMIES);

    // Populating each enemy in the enemies list.
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy;

        enemy.size = 20;
        enemy.boundingBox = (Rectangle) {0, 0, enemy.size, enemy.size};
        enemy.origin = (Vector2) {enemy.size / 2, enemy.size / 2};
        enemy.rotation = 0;
        enemy.isAlive = false;
        enemy.velocity = 2;

        enemies[i] = enemy;
    }

    return enemies;
}

void spawnEnemy(Enemy *enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].isAlive) {
            enemies[i].isAlive = true;

            int spawnFrom = rand() % 4;

            switch (spawnFrom) {
                case 0:
                    enemies[i].boundingBox.y = 0;
                    enemies[i].boundingBox.x = rand() % screenWidth;
                    break;
                case 1:
                    enemies[i].boundingBox.y = screenHeight;
                    enemies[i].boundingBox.x = rand() % screenWidth;
                    break;
                case 2:
                    enemies[i].boundingBox.y = rand() % screenHeight;
                    enemies[i].boundingBox.x = 0;
                    break;
                case 3:
                    enemies[i].boundingBox.y = rand() % screenHeight;
                    enemies[i].boundingBox.x = screenWidth;
                    break;
            }

            break;
        }
    }
}

void updateEnemies(Enemy *enemies, Player player) {
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
         // Work out the rotation of the player.
        float yDifference = player.boundingBox.y - enemies[i].boundingBox.y;
        float xDifference = player.boundingBox.x - enemies[i].boundingBox.x;

        float rotation = atan2(-xDifference, yDifference);
            
        enemies[i].rotation = (rotation / (2 * PI)) * 360; 

        enemies[i].boundingBox.x += enemies[i].velocity * -sinf(rotation);
        enemies[i].boundingBox.y += enemies[i].velocity * cosf(rotation);


    }

}

void drawEnemies(Enemy *enemies, Player player) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].isAlive) {

            DrawRectanglePro(enemies[i].boundingBox, enemies[i].origin, enemies[i].rotation, BLUE);
        }
    }

}

bool isPlayerDead(Enemy* enemies, Player player) {
    // There is a more efficient way but this game is simple.
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].isAlive) {
            if (CheckCollisionRecs(player.boundingBox, enemies[i].boundingBox))
                return true;
        }
    }

    printf("made a change bruh");

    return false;
}

void killEnemies(Enemy* enemies, Bullet* bullets) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        for (int j = 0; j < MAX_ENEMIES; j++) {
            if (enemies[j].isAlive && bullets[i].isActive) {
                if (CheckCollisionRecs(bullets[i].boundingBox, enemies[j].boundingBox)) {
                    enemies[j].isAlive = false;
                    bullets[i].isActive = false;
                }
            }
        }
    } 
}




