#include <iostream>
#include "assets/Obstacle.h"
#include <raygui.h>
#include <raylib.h>
#include <cstdint>
#include "assets/Cell.h"

#define RAYGUI_IMPLEMENTATION
//#include <raygui.h>

void DrawConnectingBoundingBox(std::pair<Vector2, Vector2> inLeft, std::pair<Vector2, Vector2> inRight, Color color)
{
   Vector2 midStart = Vector2(inLeft.first.x + inLeft.second.x, std::min(inLeft.first.y, inRight.first.y));
   int midWidth = inRight.first.x - (inLeft.first.x + inLeft.second.x);
   int midHeight = std::max(inLeft.first.y + inLeft.second.y, inRight.first.y + inRight.second.y) -
                   std::min(inLeft.first.y, inRight.first.y);
   DrawRectangleLines(midStart.x, midStart.y, midWidth, midHeight, color);
}

std::pair<Vector2, Vector2> DrawPolygonBoundingBox(const Vector2 vertices[], const int start, const int end, Color color)
{
   //check if any vertices to use
   if (end - start > 0)
   {
      //create trackers for best results in all directions
      int maxX, maxY, minX, minY;

      //init best results to first vertex data
      maxX = minX = vertices[start].x;
      maxY = minY = vertices[start].y;

      //loop through remaining vertices
      for (int i = start; i < end; i++)
      {
         //check both mins and maxs to see if new ones are found
         if (vertices[i].x < minX) minX = vertices[i].x; //minX
         if (vertices[i].x > maxX) maxX = vertices[i].x; //maxX
         if (vertices[i].y < minY) minY = vertices[i].y; //minY
         if (vertices[i].y > maxY) maxY = vertices[i].y; //maxY
      }

      //once all vertices have been evaluated, draw the final box
      DrawRectangleLines(minX, minY, maxX - minX, maxY - minY, color);

      //return the size of the bounding box generated
      return std::pair<Vector2, Vector2>(Vector2(minX, minY), Vector2(maxX - minX, maxY - minY));
   }
   else
   {
      return std::pair<Vector2, Vector2>(Vector2(0, 0), Vector2(0,0));
   }
}

void DrawPolgyonFromVertices(const Vector2 vertices[], const int numVertices)
{
   //for each vertex in shape
   for (int i = 0; i < numVertices; i++)
   {
      //draw a line from this index to the next, and wrap if on the last index
      DrawLineV(vertices[i], vertices[(i + 1) % numVertices], WHITE);
   }
}

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

    Vector2 b, t;

    Cell** cellGrid = new Cell*[64];
    for (int i = 0; i < 64; i++)
    {
       cellGrid[i] = new Cell[48];
       for (int j = 0; j < 48; j++)
       {
          b = Vector2(25 + (i * 10), 25 + ((j + 1) * 10));
          t = Vector2(25 + ((i + 1) * 10), 25 + (j * 10));
          cellGrid[i][j] = Cell(b, t);
       }
    }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        
        BeginDrawing();
        ClearBackground(BLACK);
        /*
        DrawPolgyonFromVertices(shape1, 8);
        std::pair<Vector2, Vector2> boxSpecs = DrawPolygonBoundingBox(shape1Sorted, 0, 8, RED);
        std::pair<Vector2, Vector2> lhs = DrawPolygonBoundingBox(shape1Sorted, 0, 4, ORANGE);
        std::pair<Vector2, Vector2> rhs = DrawPolygonBoundingBox(shape1Sorted, 4, 8, ORANGE);
        DrawConnectingBoundingBox(lhs, rhs, ORANGE);

        lhs = DrawPolygonBoundingBox(shape1Sorted, 0, 2, YELLOW);
        rhs = DrawPolygonBoundingBox(shape1Sorted, 2, 4, YELLOW);
        DrawConnectingBoundingBox(lhs, rhs, YELLOW);

        lhs = DrawPolygonBoundingBox(shape1Sorted, 0, 1, GREEN);
        rhs = DrawPolygonBoundingBox(shape1Sorted, 1, 2, GREEN);
        DrawConnectingBoundingBox(lhs, rhs, GREEN);

        lhs = DrawPolygonBoundingBox(shape1Sorted, 2, 3, GREEN);
        rhs = DrawPolygonBoundingBox(shape1Sorted, 3, 4, GREEN);
        DrawConnectingBoundingBox(lhs, rhs, GREEN);

        lhs = DrawPolygonBoundingBox(shape1Sorted, 4, 6, YELLOW);
        rhs = DrawPolygonBoundingBox(shape1Sorted, 6, 8, YELLOW);
        DrawConnectingBoundingBox(lhs, rhs, YELLOW);

        lhs = DrawPolygonBoundingBox(shape1Sorted, 4, 5, GREEN);
        rhs = DrawPolygonBoundingBox(shape1Sorted, 5, 6, GREEN);
        DrawConnectingBoundingBox(lhs, rhs, GREEN);

        lhs = DrawPolygonBoundingBox(shape1Sorted, 6, 7, GREEN);
        rhs = DrawPolygonBoundingBox(shape1Sorted, 7, 8, GREEN);
        DrawConnectingBoundingBox(lhs, rhs, GREEN);
        */

        // Implementations for the different types of squares
        // Uncomment below to use implementation
        
        // Base dimensions for the square
        float xPos = 200;
        float yPos = 25;
        float width = 400;
        float height = 400;

        // Verticies of the purple square

        Vector2 vertex1 = Vector2((xPos), (height + yPos)); // Bottom left
        Vector2 vertex2 = Vector2((xPos), (yPos)); // Top left
        Vector2 vertex3 = Vector2((xPos + width), (height + yPos)); // Bottom right
        Vector2 vertex4 = Vector2((xPos + width), (yPos)); // Top right

        // Mid points for each side of the square
        Vector2 bottomMiddle = Vector2((xPos + xPos), height + yPos);
        Vector2 topMiddle = Vector2((xPos + xPos), yPos);
        Vector2 leftMiddle = Vector2(xPos, (height / 2));
        Vector2 rightMiddle = Vector2(xPos + width, (height / 2));
        
        Obstacle obstacle = Obstacle(shape1, 10);
        
        obstacle.CalculateBoundingBox();

        /*Obstacle squareObstacle = Obstacle(shape2, 4);
        squareObstacle.DrawObstacle();
        squareObstacle.CalculateBoundingBox();
        squareObstacle.DrawBoundingBox();*/
        
        for (int i = 0; i < 64; i++)
        {
           for (int j = 0; j < 48; j++)
           {
              cellGrid[i][j].DrawCellByOverlapData(obstacle.CheckCollisionOfCell(cellGrid[i][j]), true);
           }
        }

        //draw in the actual obstacle
        obstacle.DrawObstacle();
        obstacle.DrawBoundingBox();

        EndDrawing();
    }

    for (int i = 0; i < 8; i++)
    {
       delete[] cellGrid[i];
    }

    delete[] cellGrid;

    CloseWindow();
    return 0;
}