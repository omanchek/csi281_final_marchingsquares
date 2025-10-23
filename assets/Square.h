#ifndef SQUARE_H
#define SQUARE_H

#include <raylib.h>

class Square
{
   public:
      Square();
      Square(Vector2 inBottomLeft, Vector2 inTopRight);
      Square(Vector2 inBottomLeft, float inHeight, float inWidth);
      ~Square();

   protected:
      Vector2 bottomLeft;
      Vector2 topRight;
};

#endif