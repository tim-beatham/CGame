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
        star.position = (Vector2) { rand() % screenWidth, 
                                rand() % screenHeight};
   
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


