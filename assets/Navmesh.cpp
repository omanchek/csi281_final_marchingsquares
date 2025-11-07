#include <iostream>
#include "Navmesh.h"

NavMesh::NavMesh()
{
   cellGrid = nullptr;
}

NavMesh::NavMesh(Vector2 baseOffset, int inCellSize, int inHorizontal, int inVertical)
{
   //copy in params
   cellSize = inCellSize;
   horizontal = inHorizontal;
   vertical = inVertical;

   //define vectors to store bottom left and top right points
   Vector2 b, t;

   //init the columns of the cell grid
   cellGrid = new Cell*[horizontal];

   //for each column
   for (int i = 0; i < horizontal; i++)
   {
      //add a new array for the row
      cellGrid[i] = new Cell[vertical];

      //populate each row with a cell in the correct spot
      for (int j = 0; j < vertical; j++)
      {
         b = Vector2(baseOffset.x + (i * cellSize), baseOffset.y + ((j + 1) * cellSize));
         t = Vector2(baseOffset.x + ((i + 1) * cellSize), baseOffset.y + (j * cellSize));
         cellGrid[i][j] = Cell(b, t);
      }
   }
}

NavMesh::~NavMesh()
{
   std::cout << "NAVMESH CLEARED" << std::endl;

   //delete each column
   for (int i = 0; i < horizontal; i++)
   {
      delete[] cellGrid[i];
   }

   //delete the structure as a whole
   delete[] cellGrid;
}

void NavMesh::DrawNavmesh(Obstacle& obstacle)
{
   //draw all of the cells based on the given obstacle
   for (int i = 0; i < horizontal; i++)
   {
      for (int j = 0; j < vertical; j++)
      {
         cellGrid[i][j].DrawCellByOverlapData(obstacle.CheckCollisionOfCell(cellGrid[i][j]), true);
      }
   }
}