#ifndef SQUARE_H
#define SQUARE_H

#include <raylib.h>

struct OverlapData
{
   OverlapData();
   OverlapData(bool inBL, bool inBR, bool inTL, bool inTR);

   bool AnyOverlaps();
   void DebugPrintOverlapResults();
   void operator=(const OverlapData& rhs);
   void operator+(const OverlapData& rhs);
   void operator+=(const OverlapData& rhs);

   bool bLeft, bRight, tLeft, tRight;
};

class Square
{
   public:
      Square();
      Square(Vector2 inBottomLeft, Vector2 inTopRight);
      Square(Vector2 inBottomLeft, float inHeight, float inWidth);
      ~Square();

      void Draw(Color colorToDraw);

      //accessors
      Vector2 GetBottomLeft();
      Vector2 GetBottomRight();
      Vector2 GetCenter();
      Vector2 GetTopLeft();
      Vector2 GetTopRight();

      float GetHeight();
      float GetWidth();

   protected:
      Vector2 bottomLeft;
      Vector2 bottomRight;
      Vector2 topLeft;
      Vector2 topRight;

      float height;
      float width;
};

#endif