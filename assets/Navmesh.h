#ifndef NAVMESH_H
#define NAVMESH_H

#include "Cell.h"
#include "NavData.h"
#include <raylib.h>
#include <vector>

class NavMesh
{
   public:
      NavMesh();
      ~NavMesh();

      NavPath GetPathToPoint(Vector2 origin, Vector2 destination);
      NavPath GetPathToPoint(Cell origin, Cell destination);
};

#endif