#include "Square.h"

Square::Square()
{
   bottomLeft = Vector2(0,100);
   topRight = Vector2(100, 0);
}

Square::Square(Vector2 inBottomLeft, Vector2 inTopRight)
{
   bottomLeft = inBottomLeft;
   topRight = inTopRight;
}

Square::Square(Vector2 inBottomLeft, float inHeight, float inWidth)
{
   bottomLeft = inBottomLeft;
   topRight = Vector2(inBottomLeft.x + inWidth, inBottomLeft.y - inHeight);
}

Square::~Square()
{

}

Vector2 Square::GetBottomLeft()
{
   return bottomLeft;
}

Vector2 Square::GetBottomRight()
{
   return Vector2(topRight.x, bottomLeft.y);
}

Vector2 Square::GetTopLeft()
{
   return Vector2(bottomLeft.x, topRight.y);
}

Vector2 Square::GetTopRight()
{
   return topRight;
}