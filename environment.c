#include "raylib.h"
#include <stdlib.h>
#include "main.h"


/**
 * @brief Creates an array of stars.
 * 
 * @return Star* A point to the first element in the array.
 */
Star *instantiateStars() {
    // Allocate memory for the stars.
    Star *stars = (Star*) malloc (NUM_STARS * sizeof(Star));

    // Now create the stars.
    for (int i = 0; i < NUM_STARS; i++) {
        // The star structure we are using.
        Star star;

        // Place the star in a random position on the screen.
        star.position = (Vector2) { rand() % 
                            (int) (worldWidth + 1.5 * screenWidth), 
                            rand() % (int) (worldHeight + 1.5 * screenHeight)};
   
        star.size = rand() % MAX_STAR_SIZE;

        star.color = (Color) {244, 247, 118, 255};

        stars[i] = star;  

    }

    return stars;
}

/**
 * @brief Draws all the stars in the stars array.
 * 
 * @param stars The stars to draw.
 */
void drawStars(Star *stars) {
    for (int i = 0; i < NUM_STARS; i++) {
        DrawRectangleV(stars[i].position, (Vector2) {stars[i].size, 
                                    stars[i].size}, stars[i].color);
    }
}

/**
 * @brief Creates a dust array.
 * 
 * @return Dust* An array of dust.
 */
Dust *instantiateDust() {
    Dust *dusts = (Dust*) malloc(NUM_DUST * sizeof(Dust));

    for (int i = 0; i < NUM_DUST; i++) {
        Dust dust;

        // Place the star in a random position on the screen.
        dust.position = (Vector2) { rand() % (int) (worldWidth + 3 * screenWidth), 
                                rand() % (int) (worldHeight + 3 * screenHeight)};

        dust.size = rand() % MAX_STAR_SIZE;

        dust.color = (Color) {255, 255, 255, 255};

        dusts[i] = dust;
    }

    return dusts;
}

/**
 * @brief Draws each dust element.
 * 
 * @param dust The dust we want to draw to the screen.
 */
void drawDust(Dust *dust) {
    for (int i = 0; i < NUM_DUST; i++) {
        DrawRectangleV(dust[i].position, (Vector2) {dust[i].size, 
                                    dust[i].size}, dust[i].color);
    }
}

/**
 * @brief Moves the dust by an offset this is used for parallax.
 * 
 * @param dust An array of dust.
 * @param offsetX The x offset to move the dust by.
 * @param offsetY The y offset to move the dust by.
 */
void moveDust(Dust *dust, float offsetX, float offsetY) {
    for (int i = 0; i < NUM_DUST; i++) {
        dust[i].position.x += offsetX;
        dust[i].position.y += offsetY;
    }
}

/**
 * @brief Moves the stars by a given offset which is used for parallax.
 * 
 * @param dust An arry of stars which we want to offset for parallax.
 * @param offsetX The x offset for parallax.
 * @param offsetY The y offset for parallax.
 */
void moveStars(Star *stars, float offsetX, float offsetY) {
    for (int i = 0; i < NUM_DUST; i++) {
        stars[i].position.x += offsetX;
        stars[i].position.y += offsetY;
    }
}

/**
 * @brief Checks if a player is in the playing space.
 * 
 * @param player The players bounding box.
 * @param worldRect The worlds bounding box.
 * @return true if the two entities collide.
 * @return false if the two entities do not collide.
 */
bool playerInBounds(Rectangle player, Rectangle worldRect) {
    return CheckCollisionRecs(player, worldRect);
}



