#ifndef MAIN
#define MAIN

#include "raylib.h"

typedef struct {
    float velocity;
    bool isActive;
    float angle;
    float size;
    Vector2 origin;
    Rectangle boundingBox;
} Bullet;

typedef struct {
    Rectangle boundingBox;
    int size;
    float rotation;
    Vector2 origin;
    bool isAlive;
    float velocity;
} Player;


typedef struct {    
    Rectangle boundingBox;
    int size;
    float rotation;
    bool isAlive;
    Vector2 origin;
    float velocity;
} Enemy;


Bullet *instantiateBullets();
Player instantiatePlayer();
Enemy *instantiateEnemies();
void fire(Bullet *bullets, float playerPosX, float playerPosY, float angle);
void drawBullets(Bullet *bullets);
void updateBullets(Bullet *bullets);
void movePlayer(Player* player);
void drawEnemies(Enemy* enemies, Player player);
void spawnEnemy(Enemy* enemies);
bool isPlayerDead(Enemy* enemies, Player player);
void killEnemies(Enemy* enemies, Bullet* bullets);
void updateEnemies(Enemy* enemies, Player player);
void reset(Enemy* enemies, Player *player);
#endif