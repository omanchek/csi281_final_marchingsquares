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