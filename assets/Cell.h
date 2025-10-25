#ifndef CELL_H
#define CELL_H

#include "Square.h"

class Cell : public Square
{
   public:
      Cell();
      ~Cell();
      void DrawValueOne();

   private:
      //NICHOLAS NOTE: Changed these to vectors. I believe this will be better in the future
      Vector2 bottomLeft;
      Vector2 bottomRight;
      Vector2 topLeft;
      Vector2 topRight;

      Vector2 bottomCenter;
      Vector2 leftCenter;
      Vector2 topCenter;
      Vector2 rightCenter;
};

#endif