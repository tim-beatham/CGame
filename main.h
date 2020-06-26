#ifndef MAIN
#define MAIN

#include "raylib.h"

#define MAX_BULLETS 10


const int screenWidth = 1024;
const int screenHeight = 768;


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


#define MAX_ENEMIES 20

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
void drawBullets(Bullet *bullets);
void updateBullets(Bullet *bullets);
void movePlayer(Player* player);
void fire(Bullet *bullets, float playerPosX, float playerPosY, float angle);
bool isPlayerDead(Enemy* enemies, Player player);
void reset(Enemy* enemies, Player *player);


Enemy *instantiateEnemies();
void drawEnemies(Enemy* enemies, Player player);
void spawnEnemy(Enemy* enemies);
void killEnemies(Enemy* enemies, Bullet* bullets);
void updateEnemies(Enemy* enemies, Player player);

void freeDataStructs(Enemy *enemies, Bullet *bullet);



#endif