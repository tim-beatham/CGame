#ifndef MAIN
#define MAIN

#include "raylib.h"

#define MAX_BULLETS 20

#define PLAYER_SPEED 100.0f
#define ENEMY_SPEED 100.0f
#define BULLET_SPEED 1000.0f
#define CAM_SPEED 30.0f

#define NUM_STARS 2000

#define MAX_STAR_SIZE 6
#define MAX_DUST_SIZE 10

#define NUM_DUST 1000

const int screenWidth = 1024;
const int screenHeight = 768;

const int worldWidth = 5000;
const int worldHeight = 4000;

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


#define MAX_ENEMIES 100

typedef struct {    
    Rectangle boundingBox;
    int size;
    float rotation;
    bool isAlive;
    Vector2 origin;
    float velocity;
} Enemy;


typedef struct {
    int size;
    Vector2 position;
    Color color;
} Dust;

// Drawing a star in the background.
typedef struct {
    int size;
    Vector2 position;
    Color color;
} Star;

typedef struct {
    Camera2D cam;
    float velocity;
} CamStruct;


Bullet *instantiateBullets();
Player instantiatePlayer();
void drawBullets(Bullet *bullets);
void updateBullets(Bullet *bullets, float elapsedTime);
void movePlayer(Player* player, float elapsedTime, Camera2D camera,
                                Dust *dust, Star *stars, Rectangle worldRect);

void fireNormal(Bullet *bullets, float playerPosX, float playerPosY, 
                                                            float angle);
void fireScatter(Bullet *bullets, float playerPosX, float playerPosY);


bool isPlayerDead(Enemy* enemies, Player player);
void reset(Enemy* enemies, Player *player, CamStruct *camera);


Enemy *instantiateEnemies();
void drawEnemies(Enemy* enemies, Player player);
void spawnEnemy(Enemy* enemies);
void killEnemies(Enemy* enemies, Bullet* bullets);
void updateEnemies(Enemy* enemies, Player player, float elapsedTime);

void freeDataStructs(Enemy *enemies, Bullet *bullet);


// Draws stars in the background.
void drawStars(Star *stars);
Star *instantiateStars();

Dust *instantiateDust();
void moveDust(Dust *dust, float offSetX, float offSetY);
void drawDust(Dust *dust);
void moveStars(Star *dust, float offSetX, float offSetY);

bool playerInBounds(Rectangle player, Rectangle worldRect);



CamStruct instantiateCamera(float startPosX, float startPosY);
void updateCamera(CamStruct *camera, Player player, 
                Dust *dust, Star *stars, float elapsedTime);
  
#endif