#include <iostream>
#include <list>
#include "Navmesh.h"
#include <unordered_map>
#include <utility>

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
   cellGrid = new Cell**[horizontal];

   //for each column
   for (int i = 0; i < horizontal; i++)
   {
      //add a new array for the row
      cellGrid[i] = new Cell*[vertical];

      //populate each row with a cell in the correct spot
      for (int j = 0; j < vertical; j++)
      {
         //add the cell and the right position / coordinates, and store those in the cell for reference
         b = Vector2(baseOffset.x + (i * cellSize), baseOffset.y + ((j + 1) * cellSize));
         t = Vector2(baseOffset.x + ((i + 1) * cellSize), baseOffset.y + (j * cellSize));
         cellGrid[i][j] = new Cell(b, t);
         cellGrid[i][j]->SetCoordinatesInNavmesh(i, j);
      }
   }
}

NavMesh::~NavMesh()
{
   std::cout << "NAVMESH CLEARED" << std::endl;

   //delete all obstacles
   for (Obstacle* it : obstacles)
   {
      delete it;
   }

   //create iterators
   int i, j;

   //delete each column
   for (i = 0; i < horizontal; i++)
   {
      //detelet all of the cells
      for (j = 0; j < vertical; j++)
      {
         delete cellGrid[i][j];
      }
      delete[] cellGrid[i];
   }

   //delete the structure as a whole
   delete[] cellGrid;
}

void NavMesh::DrawNavmesh()
{
   //create iterators
   int i, j;
   OverlapData dataIt;

   //draw all of the cells based on the given obstacle
   for (i = 0; i < horizontal; i++)
   {
      for (j = 0; j < vertical; j++)
      {
         //re-init the overlap data
         dataIt = OverlapData();

         //for each obstacle, add any new overlaps
         for (auto& it : obstacles)
         {
            dataIt += it->CheckCollisionOfCell(*cellGrid[i][j]);
         }

         //draw based on the sum of overlaps
         cellGrid[i][j]->DrawCellByOverlapData(dataIt, true);
      }
   }
}

float NavMesh::EstDist(Vector2Int diff)
{
   return sqrt(pow(float(diff.x * cellSize), 2) + pow(float(diff.y * cellSize), 2));
}

Cell* NavMesh::GetCell(int x, int y)
{
   //if cell is within map, return it
   if (IsValidCell(Vector2Int(x, y)))
   {
      return cellGrid[x][y];
   }
   else
   {
      return nullptr;
   }
}

NavPath NavMesh::GetPathToPoint(Vector2Int origin, Vector2Int destination)
{
   //check cells are different, and that both in bounds
   if (origin != destination && IsValidCell(origin) && IsValidCell(destination))
   {
      //create data structures for determining a path
      std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>> frontier = std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>>();
   
      return NavPath();
   }
   else
   {
      return NavPath();
   }
}

NavPath NavMesh::GetPathToPoint(Cell origin, Cell destination)
{
   //just call the vector2Int version w/ the cell coordinations of origin and destination
   return GetPathToPoint(origin.GetCellCoordinate(), destination.GetCellCoordinate());
}

bool NavMesh::IsValidCell(Vector2Int tileCoords)
{
   return (tileCoords >= Vector2Int(0, 0) && tileCoords < Vector2Int(horizontal, vertical));
}

void NavMesh::PushNeighbors(CellData cell, Vector2Int& dest, std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>>& inFrontier)
{
   
}

void NavMesh::RegisterObstacle(Obstacle* inObstacle)
{
   //add this obstacle to the obstacle list
   obstacles.push_back(inObstacle);
}