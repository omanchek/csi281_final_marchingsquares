#ifndef NAVMESH_H
#define NAVMESH_H

#include "Cell.h"
#include "NavData.h"
#include "Obstacle.h"
#include <raylib.h>
#include <vector>

class NavMesh
{
   public:
      NavMesh();
      NavMesh(Vector2 baseOffset, int inCellSize, int inHorizontal, int inVertical);
      ~NavMesh();

      void DrawNavmesh();

      NavPath GetPathToPoint(Vector2 origin, Vector2 destination);
      NavPath GetPathToPoint(Cell origin, Cell destination);
      void RegisterObstacle(Obstacle* inObstacle);

   private:
      Cell** cellGrid;
      std::vector<Obstacle*> obstacles;
      int cellSize, horizontal, vertical;
};

#endif