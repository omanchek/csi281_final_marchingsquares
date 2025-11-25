#include <iostream>
#include "assets/Obstacle.h"
#include "assets/Navmesh.h"
#include "assets/NavMeshAgent.h"
#include <raygui.h>
#include <raylib.h>
#include <cstdint>
#include "assets/Cell.h"

/*
* Used this forum thread to figure out how to delay the program for a certain amount of time
* https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
*/
#include <chrono>
#include <thread>

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

    InitWindow(screenWidth, screenHeight, "Marching Squares");

    SetTargetFPS(60);

    //define the navmesh and obstacles
    NavMesh* navMesh = new NavMesh(Vector2(25, 25), 10, 64, 60);
    Obstacle* obstacle = new Obstacle(shape1, 10);
    Obstacle* obstacle2 = new Obstacle(shape2, 3);
    Obstacle* obstacle3 = new Obstacle(shape3, 4);

    //register any obstacles
    navMesh->RegisterObstacle(obstacle);
    navMesh->RegisterObstacle(obstacle2);
    navMesh->RegisterObstacle(obstacle3);

    navMesh->DrawNavmesh();
    NavPath path = navMesh->GetPathToPoint(Vector2Int(1, 1), Vector2Int(55, 59));
    std::cout << path.GetSize() << std::endl;

    NavMeshAgent agent(path);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        //draw the navmesh
        navMesh->DrawNavmesh();        
        path.DrawPath();

        //draw in the actual obstacle
        obstacle3->DrawObstacle();
        obstacle2->DrawObstacle();
        obstacle->DrawObstacle();

        // Draws the agent that moves around the navmesh
        agent.draw();
        // Moves the agent to the next cell
        agent.MoveAgent();

        EndDrawing();
    }

    delete navMesh;

    CloseWindow();
    return 0;
}