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
    std::vector<Obstacle*> obstacles = std::vector<Obstacle*>();
    obstacles.push_back(new Obstacle(shape1, 10));
    obstacles.push_back(new Obstacle(shape2, 3));
    obstacles.push_back(new Obstacle(shape3, 4));

    //register any obstacles
    for (int i = 0; i < obstacles.size(); i++)
    {
      navMesh->RegisterObstacle(obstacles[i]);
    }

    //setup the navmesh and the initial path that the agent will follow
    navMesh->BakeNavmesh();
    NavPath path = navMesh->GetPathToPoint(Vector2Int(1, 1), Vector2Int(55, 59));
    std::cout << path.GetSize() << std::endl;

    //initialize the agent for the first path
    NavMeshAgent agent(path, Vector2(0,0));

    //create storage for additional points used in drawing more obstacles
    std::vector<Vector2> shapePoints;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        //check if there are points to add for shape draw
        if (IsMouseButtonPressed(1))
        {
           //store the current mouse position
           Vector2 mousePos = GetMousePosition();

           //check if the point is within the acceptance radius to loop
           if (shapePoints.size() > 0)
           {
               //calculate the difference between this click and the first point
               Vector2 deltaToFirst = Vector2(shapePoints[0].x - mousePos.x, shapePoints[0].y - mousePos.y);
               float deltaLength = sqrt(pow(deltaToFirst.x, 2) + pow(deltaToFirst.y, 2));

               //check if within dist to close the shape
               if (deltaLength < 20 && shapePoints.size() >= 3)
               {
                  //create a new obstacle based on the points draw, and register it with the navmesh to begin drawing it
                  Obstacle* newObstacle = new Obstacle(shapePoints);
                  obstacles.push_back(newObstacle);
                  navMesh->RegisterObstacle(newObstacle);
                  shapePoints.clear();

                  //rebake the navmesh to include the new obstacle
                  navMesh->BakeNavmesh();

                  //check if the new shape is overlapping the agent, and warp the agent if so
                  if (newObstacle->CheckPointInsideShape(agent.GetCenter(), false))
                  {
                     agent.SetCenter(navMesh->GetCell(Vector2Int(0,0))->GetCenter());
                  }

                  //force the agent to stop
                  agent.Stop();
                  path.ClearPath();
               }
               else
               {
                  shapePoints.push_back(mousePos);
               }
           }
           else
           {
              shapePoints.push_back(mousePos);
           }
        }

        //check if the goal has been adjusted
        if (IsMouseButtonPressed(0))
        {
           Vector2Int currentAgentCell = navMesh->GetCellFromPosition(agent.GetCenter());
           Vector2Int mouseCell = navMesh->GetCellFromPosition(GetMousePosition());
           path = navMesh->GetPathToPoint(currentAgentCell, mouseCell);
           agent = NavMeshAgent(path, agent.GetCenter());
        }

        //draw the navmesh
        navMesh->DrawNavmesh(IsKeyDown(KEY_D));        
        path.DrawPath();

        //draw in the actual obstacles
        for (int i = 0; i < obstacles.size(); i++)
        {
           obstacles[i]->DrawObstacle();

           //check if should draw the bounding box
           if (IsKeyDown(KEY_B)) obstacles[i]->DrawBoundingBox();
        }

        // Draws the agent that moves around the navmesh
        agent.draw();
        // Moves the agent to the next cell
        agent.MoveAgent();

        //draw the in-progress shape if there is one
        if (shapePoints.size() > 1)
        {
           for (int i = 0; i < shapePoints.size() - 1; i++)
           {
              DrawLine(shapePoints[i].x, shapePoints[i].y, shapePoints[i + 1].x, shapePoints[i + 1].y, RED);
           }
        }

        EndDrawing();
    }

    //cleanup memory
    delete navMesh;
    while (obstacles.size() > 0) obstacles.pop_back();


    CloseWindow();
    return 0;
}