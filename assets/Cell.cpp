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
}

Cell::~Cell()
{

}

void Cell::DrawValueOne()
{

}

bool Cell::DrawCellByCase(unsigned int caseValue)
{
   switch (caseValue)
   {
      case 0:
         return false;

      default:
         return false;
   }
}