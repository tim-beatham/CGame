#ifndef MAIN
#define MAIN

#include "raylib.h"

#define MAX_BULLETS 20

#define PLAYER_SPEED 100.0f
#define ENEMY_SPEED 100.0f
#define BULLET_SPEED 1000.0f

#define NUM_STARS 100

#define MAX_STAR_SIZE 5

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

enum BulletType {
    NORMAL,
    SCARRER
};

Bullet *instantiateBullets();
Player instantiatePlayer();
void drawBullets(Bullet *bullets);
void updateBullets(Bullet *bullets, float elapsedTime);
void movePlayer(Player* player, float elapsedTime);

void fireNormal(Bullet *bullets, float playerPosX, float playerPosY, 
                                                            float angle);
void fireScatter(Bullet *bullets, float playerPosX, float playerPosY);


bool isPlayerDead(Enemy* enemies, Player player);
void reset(Enemy* enemies, Player *player);


Enemy *instantiateEnemies();
void drawEnemies(Enemy* enemies, Player player);
void spawnEnemy(Enemy* enemies);
void killEnemies(Enemy* enemies, Bullet* bullets);
void updateEnemies(Enemy* enemies, Player player, float elapsedTime);

void freeDataStructs(Enemy *enemies, Bullet *bullet);

// Drawing a star in the background.
typedef struct {
    int size;
    Vector2 position;
    Color color;
} Star;

// Draws stars in the background.
void drawStars(Star *stars);
Star *instantiateStars();

#endif