#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <algorithm>
#include "raylib.h"
#include "Square.h"

class Obstacle
{
   public:
      Obstacle();
      Obstacle(const Vector2 vertexList[], int vertices);
      ~Obstacle();

      OverlapData CheckCollisionOfCell(Square inSquare);
      void DrawBoundingBox();
      void DrawObstacle();
      bool CalculateBoundingBox();

   private:
      int numVerts;
      Square boundingBox;
      Vector2* verts;
};

#endif