#include "Square.h"
#include <iostream>

OverlapData::OverlapData()
{
   bLeft = bRight = tLeft = tRight = false;
}

OverlapData::OverlapData(bool inBL, bool inBR, bool inTL, bool inTR)
{
   bLeft = inBL;
   bRight = inBR;
   tLeft = inTL;
   tRight = inTR;
}

void OverlapData::DebugPrintOverlapResults()
{
   std::cout << "Overlap Results: " << std::endl
             << " BottomLeft: " << bLeft << std::endl
             << " BottomRight: " << bRight << std::endl
             << " TopLeft: " << tLeft << std::endl
             << " TopRight: " << tRight << std::endl << std::endl;
}

void OverlapData::operator=(const OverlapData& rhs)
{
   bLeft = rhs.bLeft;
   bRight = rhs.bRight;
   tLeft = rhs.tLeft;
   tRight = rhs.tRight;
}

void OverlapData::operator+(const OverlapData& rhs)
{
   if (rhs.bLeft)
   {
      bLeft = true;
   }
   if (rhs.bRight)
   {
      bRight = true;
   }
   if (rhs.tLeft)
   {
      tLeft = true;
   }
   if (rhs.tRight)
   {
      tRight = true;
   }
}

void OverlapData::operator+=(const OverlapData& rhs)
{
   if (rhs.bLeft)
   {
      bLeft = true;
   }
   if (rhs.bRight)
   {
      bRight = true;
   }
   if (rhs.tLeft)
   {
      tLeft = true;
   }
   if (rhs.tRight)
   {
      tRight = true;
   }
}

Square::Square()
{
   bottomLeft = Vector2(0,100);
   topRight = Vector2(100, 0);
   height = 100;
   width = 100;
}

Square::Square(Vector2 inBottomLeft, Vector2 inTopRight)
{
   bottomLeft = inBottomLeft;
   topRight = inTopRight;
   height = inBottomLeft.y - inTopRight.y;
   width = inTopRight.x - inBottomLeft.x;
}

Square::Square(Vector2 inBottomLeft, float inHeight, float inWidth)
{
   bottomLeft = inBottomLeft;
   topRight = Vector2(inBottomLeft.x + inWidth, inBottomLeft.y - inHeight);
   height = inHeight;
   width = inWidth;
}

Square::~Square()
{

}

void Square::Draw(Color colorToDraw)
{
   //draw this square in the specified color
   DrawRectangle(bottomLeft.x, topRight.y, width, height, colorToDraw);
}

Vector2 Square::GetBottomLeft()
{
   return bottomLeft;
}

Vector2 Square::GetBottomRight()
{
   return Vector2(topRight.x, bottomLeft.y);
}

Vector2 Square::GetCenter()
{
   return Vector2((topRight.x + bottomLeft.x) / 2, (topRight.y + bottomLeft.y) / 2);
}

Vector2 Square::GetTopLeft()
{
   return Vector2(bottomLeft.x, topRight.y);
}

Vector2 Square::GetTopRight()
{
   return topRight;
}

float Square::GetHeight()
{
   return height;
}

float Square::GetWidth()
{
   return width;
}