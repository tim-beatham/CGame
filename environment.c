#include "raylib.h"
#include <stdlib.h>
#include "main.h"


Star *instantiateStars() {
    // Allocate memory for the stars.
    Star *stars = (Star*) malloc (NUM_STARS * sizeof(Star));

    // Now create the stars.
    for (int i = 0; i < NUM_STARS; i++) {
        // The star structure we are using.
        Star star;

        // Place the star in a random position on the screen.
        star.position = (Vector2) { rand() % (worldWidth + 1000), 
                                rand() % (worldHeight + 1000)};
   
        star.size = rand() % MAX_STAR_SIZE;

        star.color = (Color) {244, 247, 118, 255};

        stars[i] = star;  

        
    }

    return stars;
}


void drawStars(Star *stars) {
    for (int i = 0; i < NUM_STARS; i++) {
        DrawRectangleV(stars[i].position, (Vector2) {stars[i].size, 
                                    stars[i].size}, stars[i].color);
    }
}

Dust *instantiateDust() {
    Dust *dusts = (Dust*) malloc(NUM_DUST * sizeof(Dust));

    for (int i = 0; i < NUM_DUST; i++) {
        Dust dust;

        // Place the star in a random position on the screen.
        dust.position = (Vector2) { rand() % (worldWidth + 2000), 
                                rand() % (worldHeight + 2000)};

        dust.size = rand() % MAX_STAR_SIZE;

        dust.color = (Color) {255, 255, 255, 255};

        dusts[i] = dust;
    }

    return dusts;
}

void drawDust(Dust *dust) {
    for (int i = 0; i < NUM_DUST; i++) {
        DrawRectangleV(dust[i].position, (Vector2) {dust[i].size, 
                                    dust[i].size}, dust[i].color);
    }
}

void moveDust(Dust *dust, float offsetX, float offsetY) {
    for (int i = 0; i < NUM_DUST; i++) {
        dust[i].position.x += offsetX;
        dust[i].position.y += offsetY;
    }
}

void moveStars(Star *dust, float offsetX, float offsetY) {
    for (int i = 0; i < NUM_DUST; i++) {
        dust[i].position.x += offsetX;
        dust[i].position.y += offsetY;
    }
}

bool playerInBounds(Rectangle player, Rectangle worldRect) {
    return CheckCollisionRecs(player, worldRect);
}



