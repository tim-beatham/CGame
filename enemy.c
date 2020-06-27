#include <stdlib.h>
#include <math.h>

#include "raylib.h"
#include "main.h"


/**
 * @brief Instantiates an array of enemy structures.
 * 
 * @return Enemy* An array of enemies.
 */
Enemy *instantiateEnemies() {
    // Create an array of enemies.
    Enemy *enemies = (Enemy*) malloc(sizeof(Enemy) * MAX_ENEMIES);

    // Populating each enemy in the enemies list.
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy;
        enemy.size = 20;
        enemy.boundingBox = (Rectangle) {0, 0, enemy.size, enemy.size};
        enemy.origin = (Vector2) {enemy.size / 2, enemy.size / 2};
        enemy.rotation = 0;
        enemy.isAlive = false;
        enemy.velocity = ENEMY_SPEED;
        enemies[i] = enemy;
    }

    return enemies;
}


/**
 * @brief Spawns an enemey in the game. Places the enemy at a random
 * position outside the view of the user.
 * 
 * @param enemies An array of enemies.
 */
void spawnEnemy(Enemy *enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].isAlive) {
            enemies[i].isAlive = true;

            int spawnFrom = rand() % 4;

            switch (spawnFrom) {
                case 0:
                    enemies[i].boundingBox.y = 0;
                    enemies[i].boundingBox.x = rand() % worldWidth;
                    break;
                case 1:
                    enemies[i].boundingBox.y = worldHeight;
                    enemies[i].boundingBox.x = rand() % worldWidth;
                    break;
                case 2:
                    enemies[i].boundingBox.y = rand() % worldHeight;
                    enemies[i].boundingBox.x = 0;
                    break;
                case 3:
                    enemies[i].boundingBox.y = rand() % worldHeight;
                    enemies[i].boundingBox.x = worldWidth;
                    break;
            }
            break;
        }
    }
}

/**
 * @brief Updates all of the enemies in the game. 
 * 
 * @param enemies An array of enemies in the game.
 * @param player The player
 */
void updateEnemies(Enemy *enemies, Player player, float elapsedTime) {
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
         // Work out the rotation of the player.
        float yDifference = player.boundingBox.y - enemies[i].boundingBox.y;
        float xDifference = player.boundingBox.x - enemies[i].boundingBox.x;

        float rotation = atan2(-xDifference, yDifference);
            
        enemies[i].rotation = (rotation / (2 * PI)) * 360; 

        enemies[i].boundingBox.x += enemies[i].velocity * -sinf(rotation) 
                                                        * elapsedTime;
        enemies[i].boundingBox.y += enemies[i].velocity * cosf(rotation)
                                                        * elapsedTime;


    }

}

/**
 * @brief Draws all of the enemies in the game.
 * 
 * @param enemies An array of enemies in the game.
 * @param player The player in the game.
 */
void drawEnemies(Enemy *enemies, Player player) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].isAlive) {

            DrawRectanglePro(enemies[i].boundingBox, enemies[i].origin, 
                                                    enemies[i].rotation, BLUE);
        }
    }

}
