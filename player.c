#include<stdio.h>

#include <math.h>
#include <stdlib.h>

#include "raylib.h"
#include "main.h"


#define RUNNING_SPEED = 1.5

/**
 * @brief Instantiates the player.
 * 
 * @return Player the player structure.
 */
Player instantiatePlayer() {

    Player player;

    player.size = 25;
    player.boundingBox = (Rectangle) {worldWidth/2, worldHeight/2, 
                                            player.size, player.size};
    player.rotation = 0;
    player.origin = (Vector2) {player.size/2, player.size/2};
    player.isAlive = true;
    player.velocity = PLAYER_SPEED;

    return player;
}

/**
 * @brief Moves the player with
 * the WASD keys. Use trigonometry
 * to ensure the player moves at the 
 * same speed in each direction no 
 * matter the direction they are 
 * travelling in.
 * 
 * @param player 
 */
void movePlayer(Player* player, float elapsedTime, Camera2D camera,
                                Dust *dust, Star *stars, Rectangle worldRect) {



    // Work out the rotation of the player.
    // First need to convert the mouse position to world coordinates.
    Vector2 mouseCoords = (Vector2) {GetMouseX(), GetMouseY()};
    mouseCoords = GetScreenToWorld2D(mouseCoords, camera);


    float yDifference = mouseCoords.y - player -> boundingBox.y;
    float xDifference = mouseCoords.x - player -> boundingBox.x;

    /* Rotate the player so that it is always pointing at the mouse. */
    player -> rotation = (atan2(-xDifference, yDifference) 
                                                / (2 * PI)) * 360; 


    // Used to work out trigonometry triangles.
    float xDirection = 0;
    float yDirection = 0;

    if (player -> isAlive){
        // Work out the direction that the player is travelling in.
        if (IsKeyDown(KEY_D)) xDirection += 1;
        if (IsKeyDown(KEY_A)) xDirection -= 1;
        if (IsKeyDown(KEY_W)) yDirection -= 1;
        if (IsKeyDown(KEY_S)) yDirection += 1;

        // Work out the hypotenuse trigonometric ratio.
        float resultant = sqrtf(pow(xDirection, 2) + pow(yDirection, 2));

        float velocity = player -> velocity;
    
        // Check if the shift key has been pressed.
        if (IsKeyDown(KEY_LEFT_SHIFT)) 
            velocity *= 1.5;

        // If statement needed to prevent a divide by 0 error.
        if (resultant != 0) {
            // Work out the velocity of each component.
            player -> boundingBox.x += velocity * (xDirection / resultant) * 
                                                                elapsedTime;
            player -> boundingBox.y += velocity * (yDirection / resultant) * 
                                                                elapsedTime;
        }
    }
}


/**
 * @brief Initialise an array of all the bullets in the game/
 * 
 * @return Bullet* A pointer pointing to an array of bullets which have length
 * of MAX_BULLETS.
 */
Bullet *instantiateBullets() {
    // Instantiate an array of bullets to be used for firing.
    Bullet *bullets = (Bullet*) malloc(sizeof(Bullet) * MAX_BULLETS);

    // Set all the properties of the bullets.
    for (int i = 0; i < MAX_BULLETS; i++) {
        float size = 10;
        Bullet bullet;
        Rectangle boundingBox = {0, 0, size, size};
        bullet.boundingBox = boundingBox;
        bullet.velocity = BULLET_SPEED;
        bullet.isActive = false;
        bullet.size = size;
        bullet.angle = 0;
        bullet.origin = (Vector2) {bullet.size / 2, bullet.size / 2};
        bullet.color = (Color) { GetRandomValue(100, 255), 
                                GetRandomValue(100, 255), 
                                GetRandomValue(100, 255),
                                GetRandomValue(200, 255)};
        bullets[i] = bullet;
    }

    return bullets;
}


/**
 * @brief Fires a bullet from the player.
 * 
 * @param bullets the array of bullets.
 * @param playerPosX the x position of the player.
 * @param playerPosY the y position of the player.
 * @param angle the angle in which the player is rotated at.
 */
void fireNormal(Bullet *bullets, float playerPosX, float playerPosY, 
                                                    float angle, Sound sound) {

    // Iterate over the bullets and find one which is not active.
    Bullet *bullet = NULL;

    // Remembering to get the memory address of the bullet.
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            bullet = &bullets[i];
            break;
        }
    }

    // Fire the bullet.
    if (bullet != NULL) {
        bullet -> isActive = true;
        bullet -> boundingBox.x = playerPosX;
        bullet -> boundingBox.y = playerPosY;
        bullet -> angle = angle;
        PlaySound(sound);
    }
}


/**
 * @brief Draws the player to the world.
 * 
 * @param player The player to draw.
 */
void drawPlayer(Player player) {
    // Draw the player.
    if (player.isAlive)
        DrawPoly((Vector2) {player.boundingBox.x, player.boundingBox.y}, 
                                3, player.size, player.rotation,
                                (Color) {255, 0, 0, 200});

}


/**
 * @brief Fires all the reminaing bullets that the player has in one go.
 * 
 * @param bullets An array of bullets to fire.
 * @param playerPosX The x position of the player in the world.
 * @param playerPosY The y position of the player in the world.
 */
void fireScatter(Bullet *bullets, float playerPosX, float playerPosY,
                                            Sound sound) {

    int numBullets = 0;

    // Count how many bullets the player has to use.
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            numBullets++;
        }
    }

    // Fire bullets in all directions.
    float division = (2 * PI) / numBullets;
    float angle = 2 * PI;

    if (numBullets > 0) {
        PlaySound(sound);

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].isActive) {
                bullets[i].isActive = true;
                bullets[i].boundingBox.x = playerPosX;
                bullets[i].boundingBox.y = playerPosY;
                bullets[i].angle = angle;
                angle -= division;
            }
        }  
    }
}

/**
 * @brief draws all the bullets in the game
 * 
 * @param bullets an array of bullets.
 */
void drawBullets(Bullet *bullets) {

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            DrawRectanglePro(bullets[i].boundingBox, bullets[i].origin, 0, 
                                                        bullets[i].color);
        }
    }
}

/**
 * @brief updates all the bullets in the game.
 * 
 * @param bullets the array of bullets.
 */
void updateBullets(Bullet *bullets, float elapsedTime) {                                                    
            
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            // Update the position of the bullet.
            bullets[i].boundingBox.x += 
                                bullets[i].velocity * -sinf(bullets[i].angle) 
                                                            * elapsedTime;
            bullets[i].boundingBox.y += 
                                bullets[i].velocity * cosf(bullets[i].angle) 
                                                            * elapsedTime;

            // Check if it has gone out of the screen.

            if (bullets[i].boundingBox.x > worldWidth + 1000
                                || bullets[i].boundingBox.x < -1000 
                                || bullets[i].boundingBox.y > worldHeight + 1000
                                || bullets[i].boundingBox.y < -1000) {
                bullets[i].isActive = false;
            } 
        }
    }
}

/**
 * @brief Checks if an enemy has collided with a bullet.
 * If this is the case then we kill the enemy.
 * 
 * @param enemies A list of enemies in the game.
 * @param bullets A list of bullets in the game.
 */
void killEnemies(Enemy* enemies, Bullet* bullets, Sound sound) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        for (int j = 0; j < MAX_ENEMIES; j++) {
            if (enemies[j].isAlive && bullets[i].isActive) {
                if (CheckCollisionRecs(bullets[i].boundingBox, 
                                                enemies[j].boundingBox)) {
                    
                    enemies[j].isAlive = false;
                    bullets[i].isActive = false;
                    PlaySound(sound);
                    break;
                }
            }
        }
    } 
}

/**
 * @brief Checks if the player has collided with an enemy.
 * 
 * @param enemies An array of all the enemies in the game.
 * @param player The player in game.
 * @return true True if the player has collided with an enemy.
 * @return false False if the player has not collided with an enemy.
 */
bool isPlayerDead(Enemy* enemies, Player player) {
    // There is a more efficient way but this game is simple.
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].isAlive) {
            if (CheckCollisionRecs(player.boundingBox, enemies[i].boundingBox))
                return true;
        }
    }
    return false;
}





