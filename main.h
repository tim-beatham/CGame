#ifndef MAIN
#define MAIN

#include "raylib.h"

typedef struct {
    Vector2 position;
    float velocity;
    bool isActive;
    float angle;
    float size;
} Bullet;

typedef struct {
    Vector2 position;
    Vector2 size;
    float velocity;
    Texture2D player;
} Player;


Bullet *instantiateBullets();
Player instantiatePlayer();
void fire(Bullet *bullets, float playerPosX, float playerPosY, float angle);
void drawBullets(Bullet *bullets);
void updateBullets(Bullet *bullets);


#endif