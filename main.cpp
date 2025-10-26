#include <iostream>
#include <raylib.h>
#include <cstdint>
#include "assets/Cell.h"

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
   Vector2(150, 100),
   Vector2(200, 350),
   Vector2(300, 200),
   Vector2(400, 250),
   Vector2(600, 200),
   Vector2(500, 150)
};

Vector2 shape1Sorted[] =
{
   Vector2(50, 50),
   Vector2(100, 200),
   Vector2(150, 100),
   Vector2(200, 350),
   Vector2(300, 200),
   Vector2(400, 250),
   Vector2(500, 150),
   Vector2(600, 200)
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int imgWidth = 400;
    const int imgHeight = 400;

    InitWindow(screenWidth, screenHeight, "Pixel Manipulation");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // drawing logic goes here
        /*
        BeginDrawing();
        ClearBackground(BLACK);

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

        DrawRectangleLines(xPos, yPos, width, height, SKYBLUE);
        
        //Square Value 1
        //DrawTriangle(leftMiddle, vertex1, bottomMiddle, PINK);

        //Square Value 2
        //DrawTriangle(bottomMiddle, vertex3, rightMiddle, PINK);

        // Square Value 3
        //DrawRectangle(leftMiddle.x, leftMiddle.y, width, ((height / 2) + yPos), PINK);

        // Square value 4 *NOTE: FIGURE OUT WHY I CAN'T JUST DRAW A TRIANGLE AND HAVE TO USE TRIANGLE LINES HERE
        //DrawTriangle(topMiddle, vertex4, rightMiddle, PINK);

        // Square value 5
        //DrawRectangle(xPos, yPos, width, height, PINK);
        //DrawTriangle(bottomMiddle, vertex3, rightMiddle, BLACK);
        //DrawTriangle(topMiddle, vertex2, leftMiddle, BLACK);

        // Square value 6
        //DrawRectangle(bottomMiddle.x, topMiddle.y, (width / 2), height, PINK);

        // Square value 7
       //DrawTriangle(topMiddle, vertex2, leftMiddle, PINK);

        // Square value 8
        //DrawRectangle(xPos, yPos, width, height, PINK);
        //DrawTriangle(topMiddle, vertex2, leftMiddle, BLACK);

        // Square value 9
        //DrawRectangle((bottomMiddle.x - (bottomMiddle.x / 2)), topMiddle.y, (width / 2), height, PINK);

        // Square value 10 *NOTE: CHECK THIS ONE FOR ERROR WITH BLACK TRIANGLE 4 VALUE
        //DrawRectangle(xPos, yPos, width, height, PINK);
        //DrawTriangleLines(topMiddle, vertex4, rightMiddle, BLACK);
        //DrawTriangle(leftMiddle, vertex1, bottomMiddle, BLACK);

        // Square value 11 *NOTE: CHECK THIS ONE FOR ERROR WITH BLACK TRIANGLE 4 VALUE
        //DrawRectangle(xPos, yPos, width, height, PINK);
        //DrawTriangleLines(rightMiddle, topMiddle, vertex4, BLACK);

        // Square value 12
        //DrawRectangle(leftMiddle.x, topMiddle.y, width, ((height / 2) + yPos), PINK);

        // Square value 13
        //DrawRectangle(xPos, yPos, width, height, PINK);
        //DrawTriangle(bottomMiddle, vertex3, rightMiddle, BLACK);


        // Square value 14
        //DrawRectangle(xPos, yPos, width, height, PINK);
        //DrawTriangle(leftMiddle, vertex1, bottomMiddle, BLACK);

        // Square value 15
        //DrawRectangle(xPos, yPos, width, height, PINK);*/

        Cell cell = Cell(vertex1, vertex4);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}