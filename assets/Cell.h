#ifndef CELL_H
#define CELL_H

#include "Square.h"

class Cell : public Square
{
   public:
      Cell();
      ~Cell();

   private:
      float bottomLeft = 0;
      float bottomRight = 0;
      float topLeft = 0;
      float topRight = 0;
};

#endif