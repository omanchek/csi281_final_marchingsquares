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

Vector2 shape2[] =
{
   Vector2(500, 500),
   Vector2(600, 600),
   Vector2(650, 550)
};

Vector2 shape3[] =
{
   Vector2(300, 500),
   Vector2(275, 600),
   Vector2(425, 600),
   Vector2(400, 500)
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
    NavMesh* navMesh = new NavMesh(Vector2(25, 25), 10, 64, 60);
    Obstacle* obstacle = new Obstacle(shape1, 10);
    Obstacle* obstacle2 = new Obstacle(shape2, 3);
    Obstacle* obstacle3 = new Obstacle(shape3, 4);

    NavPath path = navMesh->GetPathToPoint(navMesh->GetCell(10, 12), navMesh->GetCell(50, 40));
    std::cout << path.GetSize() << std::endl;

    //register any obstacles
    navMesh->RegisterObstacle(obstacle);
    navMesh->RegisterObstacle(obstacle2);
    navMesh->RegisterObstacle(obstacle3);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        
        BeginDrawing();
        ClearBackground(BLACK);

        //draw the navmesh
        navMesh->DrawNavmesh();        
        path.DrawPath();

        //draw in the actual obstacle
        obstacle3->DrawObstacle();
        obstacle2->DrawObstacle();
        obstacle->DrawObstacle();
        obstacle3->DrawBoundingBox();
        obstacle2->DrawBoundingBox();
        obstacle->DrawBoundingBox();

        //navMesh.GetPathToPoint(navMesh.GetCell(0, 0), navMesh.GetCell(10, 12));

        EndDrawing();
    }

    delete navMesh;

    CloseWindow();
    return 0;
}