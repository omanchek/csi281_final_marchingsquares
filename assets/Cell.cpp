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
   bottomCenter = Vector2((bottomRight.x + bottomLeft.x)/2, bottomRight.y);
   leftCenter = Vector2((topLeft.x), ((topLeft.y + bottomLeft.y) / 2));
   topCenter = Vector2(((topRight.x + topLeft.x) / 2), topRight.y);
   rightCenter = Vector2((topRight.x), ((topRight.y + bottomRight.y) / 2));
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

    DrawCircle(bottomCenter.x, bottomCenter.y, 10, BLUE);
    DrawCircle(leftCenter.x, leftCenter.y, 10, BLUE);
    DrawCircle(topCenter.x, topCenter.y, 10, BLUE);
    DrawCircle(topCenter.x, topCenter.y, 10, BLUE);
}

bool Cell::DrawCellByCase(unsigned int caseValue)
{
   switch (caseValue)
   {
      case 0:
        return false;
      case 1:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, PINK);
        break;

      case 2:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, PINK);
        break;

      case 3:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawRectangle(leftCenter.x, leftCenter.y, (rightCenter.x - leftCenter.x), (bottomCenter.y / 2) - 12, PINK);
        break;

      case 4:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawTriangle(topCenter, rightCenter, topRight, PINK);
        break;

      case 5:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, BLACK);
        DrawTriangle(topCenter, topLeft, leftCenter, BLACK);
        break;

      case 6:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawRectangle(bottomCenter.x, topCenter.y, ((rightCenter.x - bottomCenter.x)), (bottomCenter.y - topCenter.y), PINK);
        break;

      case 7:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawTriangle(topCenter, topLeft, leftCenter, PINK);
        break;

      case 8:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
        DrawTriangle(topCenter, topLeft, leftCenter, BLACK);
        break;

      case 9:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawRectangle(bottomLeft.x, topLeft.y, ((rightCenter.x - bottomCenter.x)), (bottomCenter.y - topCenter.y), PINK);
        break;

      case 10:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
        DrawTriangle(topCenter, rightCenter, topRight, BLACK);
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, BLACK);
        break;

      case 11:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
        DrawTriangle(topCenter, rightCenter, topRight, BLACK);
        break;

      case 12:
        DrawRectangle(topLeft.x, topRight.y, (rightCenter.x - leftCenter.x), (bottomCenter.y / 2) - 12, PINK);
        break;

      case 13:
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, BLACK);
        break;

      case 14:
          DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
          DrawTriangle(leftCenter, bottomLeft, bottomCenter, BLACK);
          break;

      case 15:
          DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
          break;

      default:
         return false;
   }
}