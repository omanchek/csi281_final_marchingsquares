#include <iostream>
#include "assets/Obstacle.h"
#include "assets/Navmesh.h"
#include <raygui.h>
#include <raylib.h>
#include <cstdint>
#include "assets/Cell.h"

#define RAYGUI_IMPLEMENTATION
//#include <raygui.h>

Vector2 shape1[] = 
{
   Vector2(50, 50),
   Vector2(100, 200),
   Vector2(150, 500),
   Vector2(250, 350),
   Vector2(300, 200),
   Vector2(400, 200),
   Vector2(400, 250),
   Vector2(500, 400),
   Vector2(500, 200),
   Vector2(500, 150)
};

int main()
{
    const int screenWidth = 1080;
    const int screenHeight = 720;
    const int imgWidth = 400;
    const int imgHeight = 400;

    InitWindow(screenWidth, screenHeight, "Pixel Manipulation");

    SetTargetFPS(60);

    //define the navmesh and obstacles
    NavMesh navMesh = NavMesh(Vector2(25, 25), 10, 64, 48);
    Obstacle obstacle = Obstacle(shape1, 10);
    obstacle.CalculateBoundingBox();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        
        BeginDrawing();
        ClearBackground(BLACK);

        //draw the navmesh
        navMesh.DrawNavmesh(obstacle);

        //draw in the actual obstacle
        obstacle.DrawObstacle();
        obstacle.DrawBoundingBox();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}