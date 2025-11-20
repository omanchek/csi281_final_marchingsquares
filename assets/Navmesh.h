#ifndef NAVMESH_H
#define NAVMESH_H

#include "Cell.h"
#include "NavData.h"
#include "Obstacle.h"
#include <queue>
#include <raylib.h>
#include <vector>

struct CellData
{
   Vector2Int mSelf;
   Vector2Int mParent;
   float mG;
   float mH;

   CellData(Vector2Int self, Vector2Int parent, float g, float h) { mSelf = self; mParent = parent; mG = g; mH = h; }

   bool operator<(const CellData& rhs) const { return (mG + mH) < (rhs.mG + rhs.mH); }
   bool operator>(const CellData& rhs) const { return (mG + mH) > (rhs.mG + rhs.mH); }
};

class NavMesh
{
   public:
      NavMesh();
      NavMesh(Vector2 baseOffset, int inCellSize, int inHorizontal, int inVertical);
      ~NavMesh();

      void DrawNavmesh();
      
      float EstDist(Vector2Int diff);
      Cell GetCell(int x, int y);
      NavPath GetPathToPoint(Vector2 origin, Vector2 destination);
      NavPath GetPathToPoint(Cell origin, Cell destination);
      bool IsValidTile(Vector2Int tileCoords);
      void RegisterObstacle(Obstacle* inObstacle);

   private:
      Cell** cellGrid;
      std::vector<Obstacle*> obstacles;
      int cellSize, horizontal, vertical;
};

//bool operator<(const CellData& lhs, const CellData& rhs) { return ((lhs.mG + lhs.mH) < (rhs.mG + rhs.mH)); }
//bool operator>(const CellData& lhs, const CellData& rhs) { return ((lhs.mG + lhs.mH) > (rhs.mG + rhs.mH)); }

#endif