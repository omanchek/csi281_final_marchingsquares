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
      bool CheckPointInsideShape(Vector2 point, bool debugPrint);
      void DrawBoundingBox();
      void DrawObstacle();
      bool CalculateBoundingBox();
      bool InBetween(float value, float bound1, float bound2);
      bool RaycastSegment(Vector2 origin, int first, int second);

   private:
      int numVerts;
      Square boundingBox;
      Vector2* verts;
};

#endif