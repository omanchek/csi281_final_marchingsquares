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

      //accessors
      Vector2 GetBottomLeft();
      Vector2 GetBottomRight();
      Vector2 GetTopLeft();
      Vector2 GetTopRight();

   protected:
      Vector2 bottomLeft;
      Vector2 bottomRight;
      Vector2 topLeft;
      Vector2 topRight;
};

#endif