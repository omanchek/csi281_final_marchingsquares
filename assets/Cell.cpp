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

bool Cell::DrawCellByCase(unsigned int caseValue, Color walkable, Color blocked, bool debugDraw)
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
        // Draws case 2 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, walkable);
        break;

      case 2:
        // Draws case 3 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, walkable);
        break;

      case 3:
        // Draws case 4 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawRectangle(leftCenter.x, leftCenter.y, (rightCenter.x - leftCenter.x), ((bottomCenter.y - topCenter.y) / 2), walkable);
        break;

      case 4:
        // Draws case 5 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawTriangle(topCenter, rightCenter, topRight, walkable);
        break;

      case 5:
        // Draws case 6 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, blocked);
        DrawTriangle(topCenter, topLeft, leftCenter, blocked);
        break;

      case 6:
        // Draws case 7 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawRectangle(bottomCenter.x, topCenter.y, ((rightCenter.x - bottomCenter.x)), (bottomCenter.y - topCenter.y), walkable);
        break;

      case 7:
        // Draws case 8 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        DrawTriangle(topCenter, topLeft, leftCenter, blocked);
        break;

      case 8:
        // Draws case 9 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawTriangle(topCenter, topLeft, leftCenter, walkable);
        break;

      case 9:
        // Draws case 10 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawRectangle(bottomLeft.x, topLeft.y, ((rightCenter.x - bottomCenter.x)), (bottomCenter.y - topCenter.y), walkable);
        break;

      case 10:
        // Draws case 11 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        DrawTriangle(topCenter, rightCenter, topRight, blocked);
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, blocked);
        break;

      case 11:
        // Draws case 12 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        DrawTriangle(topCenter, rightCenter, topRight, blocked);
        break;

      case 12:
        // Draws case 13 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), blocked);
        DrawRectangle(topLeft.x, topRight.y, (rightCenter.x - leftCenter.x), ((bottomCenter.y - topCenter.y) / 2), walkable);
        break;

      case 13:
        // Draws case 14 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        DrawTriangle(bottomCenter, bottomRight, rightCenter, blocked);
        break;

      case 14:
        // Draws case 15 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        DrawTriangle(leftCenter, bottomLeft, bottomCenter, blocked);
        break;

      case 15:
        // Draws case 16 square
        DrawRectangle(bottomLeft.x, topRight.y, (bottomRight.x - bottomLeft.x), (bottomRight.y - topRight.y), walkable);
        break;

      default:
         return false;
   }
}

void Cell::DrawCellByOverlapData(OverlapData inData, Color walkable, Color blocked, bool debugDraw)
{
   //case 0
   if (inData.bLeft && inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(0, walkable, blocked, debugDraw);
   }

   //case 1
   else if (!inData.bLeft && inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(1, walkable, blocked, debugDraw);
   }

   //case 2
   else if (inData.bLeft && !inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(2, walkable, blocked, debugDraw);
   }

   //case 3
   else if (!inData.bLeft && !inData.bRight && inData.tLeft && inData.tRight)
   {
      DrawCellByCase(3, walkable, blocked, debugDraw);
   }

   //case 4
   else if (inData.bLeft && inData.bRight && inData.tLeft && !inData.tRight)
   {
      DrawCellByCase(4, walkable, blocked, debugDraw);
   }

   //case 5
   else if (!inData.bLeft && inData.bRight && inData.tLeft && !inData.tRight)
   {
      DrawCellByCase(5, walkable, blocked, debugDraw);
   }

   //case 6
   else if (inData.bLeft && !inData.bRight && inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(6, walkable, blocked, debugDraw);
   }

   //case 7
   else if (!inData.bLeft && !inData.bRight && inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(7, walkable, blocked, debugDraw);
   }

   //case 8
   else if (inData.bLeft && inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(8, walkable, blocked, debugDraw);
   }

   //case 9
   else if (!inData.bLeft && inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(9, walkable, blocked, debugDraw);
   }

   //case 10
   else if (inData.bLeft && !inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(10, walkable, blocked, debugDraw);
   }

   //case 11
   else if (!inData.bLeft && !inData.bRight && !inData.tLeft && inData.tRight)
   {
       DrawCellByCase(11, walkable, blocked, debugDraw);
   }

   //case 12
   else if (inData.bLeft && inData.bRight && !inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(12, walkable, blocked, debugDraw);
   }

   //case 13
   else if (!inData.bLeft && inData.bRight && !inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(13, walkable, blocked, debugDraw);
   }

   //case 14
   else if (inData.bLeft && !inData.bRight && !inData.tLeft && !inData.tRight)
   {
       DrawCellByCase(14, walkable, blocked, debugDraw);
   }

   //case 15
   else
   {
      DrawCellByCase(15, walkable, blocked, debugDraw);
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