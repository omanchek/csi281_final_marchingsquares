#ifndef NAVMESH_H
#define NAVMESH_H

#include <iostream>
#include "Cell.h"
#include "NavData.h"
#include "Obstacle.h"
#include <queue>
#include <raylib.h>
#include <vector>

//define the directions that can be checked when pathfinding
const int NEIGHBOR_COUNT = 4;
const Vector2Int NEIGHBOR_DIR[] = {
                                    Vector2Int(1, 0),
                                    Vector2Int(0, 1),
                                    Vector2Int(-1, 0),
                                    Vector2Int(0, -1)
                                  };

struct CellData
{
   Vector2Int mSelf; //coordinates of this cell
   CellData* mParent; //coordinates of the parent cell
   float mG; //distance travelled so far
   float mH; //estimated distance left

   CellData() { mSelf = Vector2Int(); mParent = nullptr; mG = 0; mH = 0; }
   CellData(Vector2Int self, CellData parent, float g, float h) { mSelf = self; mParent = &parent; mG = g; mH = h; }
   CellData(const CellData& other) { mSelf = other.mSelf; mParent = other.mParent; mG = other.mG; mH = other.mH; }

   void operator=(const CellData& rhs) { mSelf = rhs.mSelf; mParent = rhs.mParent; mG = rhs.mG; mH = rhs.mH; }
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
      Cell* GetCell(int x, int y);
      NavPath GetPathToPoint(Vector2Int origin, Vector2Int destination);
      NavPath GetPathToPoint(Cell origin, Cell destination);
      bool IsValidCell(Vector2Int tileCoords);
      void PushNeighbors(CellData cell, Vector2Int& dest, std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>>& inFrontier);
      void RegisterObstacle(Obstacle* inObstacle);

   private:
      Cell*** cellGrid;
      std::vector<Obstacle*> obstacles;
      int cellSize, horizontal, vertical;
};

#endif