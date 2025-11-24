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

   // assigns a value for the cell
   pathfindingValue = 1;
}

Cell::~Cell()
{

}

void Cell::DrawValueOne()
{
    DrawCircle(bottomLeft.x, bottomLeft.y, 2, GREEN);
    DrawCircle(bottomRight.x, bottomRight.y, 2, GREEN);
    DrawCircle(topLeft.x, topLeft.y, 2, GREEN);
    DrawCircle(topRight.x, topRight.y, 2, GREEN);

    DrawCircle(bottomCenter.x, bottomCenter.y, 2, BLUE);
    DrawCircle(leftCenter.x, leftCenter.y, 2, BLUE);
    DrawCircle(topCenter.x, topCenter.y, 2, BLUE);
    DrawCircle(topCenter.x, topCenter.y, 2, BLUE);
}

bool Cell::DrawCellByCase(unsigned int caseValue, bool debugDraw)
{
   //check should draw debug outline points
   if (debugDraw)
   {
      DrawValueOne();
   }

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
        DrawRectangle(leftCenter.x, leftCenter.y, (rightCenter.x - leftCenter.x), ((bottomCenter.y - topCenter.y) / 2), PINK);
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
          DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), PINK);
          DrawTriangle(topCenter, topLeft, leftCenter, BLACK);
        break;

      case 8:
          DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
          DrawTriangle(topCenter, topLeft, leftCenter, PINK);
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
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), BLACK);
        DrawRectangle(topLeft.x, topRight.y, (rightCenter.x - leftCenter.x), ((bottomCenter.y - topCenter.y) / 2), PINK);
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

void Cell::DrawCellByOverlapData(OverlapData inData, bool debugDraw)
{
   //case 0
   if (inData.bLeft && inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(0, debugDraw);
   }

   //case 1
   else if (!inData.bLeft && inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(1, debugDraw);
   }

   //case 2
   else if (inData.bLeft && !inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(2, debugDraw);
   }

   //case 3
   else if (!inData.bLeft && !inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(3, debugDraw);
   }

   //case 4
   else if (inData.bLeft && inData.bRight && inData.tLeft && !inData.tRight)
   {
      DrawCellByCase(4, debugDraw);
   }

   //case 5
   else if (!inData.bLeft && inData.bRight && inData.tLeft && !inData.tRight)
   {
      DrawCellByCase(5, debugDraw);
   }

   //case 6
   else if (inData.bLeft && !inData.bRight && inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(6, debugDraw);
   }

   //case 7
   else if (!inData.bLeft && !inData.bRight && inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(7, debugDraw);
   }

   //case 8
   else if (inData.bLeft && inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(8, debugDraw);
   }

   //case 9
   else if (!inData.bLeft && inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(9, debugDraw);
   }

   //case 10
   else if (inData.bLeft && !inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(10, debugDraw);
   }

   //case 11
   else if (!inData.bLeft && !inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(11, debugDraw);
   }

   //case 12
   else if (inData.bLeft && inData.bRight && !inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(12, debugDraw);
   }

   //case 13
   else if (!inData.bLeft && inData.bRight && !inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(13, debugDraw);
   }

   //case 14
   else if (inData.bLeft && !inData.bRight && !inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(14, debugDraw);
   }

   //case 15
   else
   {
      DrawCellByCase(15, debugDraw);
   }
}

Vector2Int Cell::GetCellCoordinate()
{
   return coordinate;
}

OverlapData Cell::GetOverlapData()
{
   return currentOverlaps;
}

Cell* Cell::GetParent()
{
   return pathParent;
}

float Cell::GetWeight()
{
   return pathfindingValue;
}

void Cell::SetCoordinatesInNavmesh(int x, int y)
{
   coordinate = Vector2Int(x, y); 
}

void Cell::SetOverlapData(OverlapData inData)
{
   currentOverlaps = inData;
}

void Cell::SetParent(Cell* parent)
{
   pathParent = parent;
}

void Cell::SetWeight(float weight)
{
   pathfindingValue = weight;
}

bool Cell::operator<(const Cell& rhs) const
{
   return (pathfindingValue < rhs.pathfindingValue);
}

bool Cell::operator>(const Cell& rhs) const
{
   return (pathfindingValue > rhs.pathfindingValue);
}