#include "Cell.h"

#include <iostream>

Cell::Cell()
{
	
}

Cell::Cell(Vector2 inBottomLeft, Vector2 inTopRight)
{
   //call square constructor to set up corners
   bottomLeft = inBottomLeft;
   topRight = inTopRight;
   bottomRight = Vector2(topRight.x, bottomLeft.y);
   topLeft = Vector2(bottomLeft.x, topRight.y);

   //Set up centeres of the cell
   bottomCenter = Vector2((bottomRight.x / 2), bottomRight.y);
   leftCenter = Vector2((topLeft.x), (topLeft.y / 2));
   topCenter = Vector2((topRight.x / 2), topRight.y);
   rightCenter = Vector2((topRight.x), (topRight.y / 2));
}

Cell::~Cell()
{

}

void Cell::DrawValueOne()
{
    DrawCircle(bottomLeft.x, bottomLeft.y, 10, GREEN);
    DrawCircle(bottomRight.x, bottomRight.y, 10, GREEN);
    DrawCircle(topLeft.x, topLeft.y, 10, GREEN);
    DrawCircle(topRight.x, topRight.y, 10, GREEN);
}

bool Cell::DrawCellByCase(unsigned int caseValue)
{
   switch (caseValue)
   {
      case 0:
        return false;
      case 1:
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, PINK);
        break;

      case 2:
        DrawTriangle(bottomCenter, bottomRight, rightCenter, PINK);
        break;

      case 3:
        DrawRectangle(leftCenter.x, leftCenter.y, (leftCenter.x + rightCenter.x), (((bottomCenter.y + topCenter.y)/ 2)), PINK);
        break;

      case 4:
        DrawTriangle(topCenter, topRight, rightCenter, PINK);
        break;

      case 5:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, BLACK);
        DrawTriangle(topCenter, topLeft, leftCenter, BLACK);
        break;

      case 6:
        DrawRectangle(bottomCenter.x, topCenter.y, ((leftCenter.x + rightCenter.x) / 2), (bottomCenter.y + topCenter.y), PINK);
        break;

      case 7:
        DrawTriangle(topCenter, topLeft, leftCenter, PINK);
        break;

      case 8:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
        DrawTriangle(topCenter, topLeft, leftCenter, BLACK);
        break;

      case 9:
        DrawRectangle((bottomCenter.x - (bottomCenter.x / 2)), topCenter.y, ((bottomLeft.x + bottomRight.x) / 2), (bottomLeft.y + bottomRight.y), PINK);
        break;

      case 10:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
        DrawTriangleLines(topCenter, topRight, rightCenter, BLACK);
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, BLACK);
        break;

      case 11:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
        DrawTriangleLines(rightCenter, topCenter, topRight, BLACK);
        break;

      case 12:
        DrawRectangle(leftCenter.x, topCenter.y, (bottomLeft.x + bottomRight.x), (((bottomLeft.y + bottomRight.y) / 2)), PINK);
        break;

      case 13:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, BLACK);
        break;

      case 14:
          DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
          DrawTriangle(leftCenter, bottomLeft, bottomCenter, BLACK);
          break;

      case 15:
          DrawRectangle(bottomLeft.x, topRight.y, (bottomLeft.x + bottomRight.x), (bottomLeft.y + bottomRight.y), PINK);
          break;

      default:
         return false;
   }
}