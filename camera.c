#include "raylib.h"
#include <math.h>
#include "main.h"


CamStruct instantiateCamera(float startPosX, float startPosY) {
    CamStruct camStruct;

    Camera2D camera = (Camera2D) { 0 };
    camera.target = (Vector2) { startPosX, startPosY};
    camera.offset = (Vector2) { screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    camStruct.cam = camera;

    camStruct.velocity = CAM_SPEED;

    return camStruct;
}

void updateCamera(CamStruct *camera, Player player,
                        Dust *dust, Star *stars, float elapsedTime) {

    float yDifference = player.boundingBox.y - 
                        camera -> cam.target.y;

    float xDifference = player.boundingBox.x -
                        camera -> cam.target.x;

    float rotation = atan2(-xDifference, yDifference);

    float offSetX = camera -> velocity * -sinf(rotation) * elapsedTime;
    float offSetY = camera -> velocity * cosf(rotation) * elapsedTime;

    camera -> cam.target.x += offSetX;
                                                
    camera -> cam.target.y += offSetY;

    moveDust(dust, -offSetX, -offSetY);
    moveStars(stars, 0.001 * offSetX, 0.001 * offSetY);

}

