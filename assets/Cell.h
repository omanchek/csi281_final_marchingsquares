#ifndef CELL_H
#define CELL_H

#include "Square.h"

const int NUM_CASES = 16;

class Cell : public Square
{
   public:
      Cell();
      Cell(Vector2 inBottomLeft, Vector2 inTopRight);
      ~Cell();
      void DrawValueOne();

      bool DrawCellByCase(unsigned int caseValue);

   private:

      Vector2 bottomCenter;
      Vector2 leftCenter;
      Vector2 topCenter;
      Vector2 rightCenter;
};

#endif