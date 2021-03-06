#ifndef GAME_H
#define GAME_H

#include "shader.h"
#include "utility.h"
#include "input.h"
#include "camera.h"
#include "line.h"
#include "collition.h"

#define global_variable static
#define WNDWIDTH 800
#define WNDHEIGHT 600
#define LEFTBUTTON 0
#define RIGHTBUTTON 1

struct Projectile
{
    Vec3 position;
    Vec3 start;
    Vec3 end;
    float speed;
    float distance;
    float planeIntersection;
    int index;
    float angle;
};

struct UI
{
    Line xAxis;
    Line yAxis;
    Shader shader;
};

struct MainGame
{
    Shader main_shader;
    Shader mesh_shader; 
    UI ui; 
    Input input;
    Camera camera;
    Terrain terrain;
    Line xAxis;
    Line yAxis;
    Line zAxis;
    Plane planes[6];
    Mesh ball;
    Projectile projectile[200];
};

void GameInit(MainGame* game);
void GameUnpdateAndRender(MainGame* game, float deltaTime);

#endif
