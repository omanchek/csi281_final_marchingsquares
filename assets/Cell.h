#ifndef CELL_H
#define CELL_H

#include "Square.h"
#include "Vector2Int.h"

const int NUM_CASES = 16;

class Cell : public Square
{
   public:
      Cell();
      Cell(Vector2 inBottomLeft, Vector2 inTopRight);
      ~Cell();
      void DrawValueOne();

      bool DrawCellByCase(unsigned int caseValue, bool debugDraw);
      void DrawCellByOverlapData(OverlapData inData, bool debugDraw);

      Vector2Int GetCellCoordinate();
      Cell* GetParent();
      float GetWeight();
      void SetCoordinatesInNavmesh(int x, int y);
      void SetParent(Cell* parent);
      void SetWeight(float weight);

      bool operator<(const Cell& rhs) const;
      bool operator>(const Cell& rhs) const;

   private:
      Vector2 bottomCenter;
      Vector2 leftCenter;
      Vector2 topCenter;
      Vector2 rightCenter;

      Vector2Int coordinate = Vector2Int();

      float pathfindingValue;
      Cell* pathParent = nullptr;
};

#endif