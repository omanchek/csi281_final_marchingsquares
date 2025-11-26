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
   offset = baseOffset;

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
         cellGrid[i][j]->DrawCellByOverlapData(dataIt, GRAY, RED, false);
         cellGrid[i][j]->SetOverlapData(dataIt);
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

Cell* NavMesh::GetCell(Vector2Int coord)
{
   return GetCell(coord.x, coord.y);
}

Vector2Int NavMesh::GetCellFromPosition(Vector2 pos)
{
   //adjust the given position based on the offset of the navmesh to simplify calculations
   Vector2 adjustedPos = Vector2(pos.x - offset.x, pos.y - offset.y);

   //determine the raw cell indices for each dimension
   int horizontalCell = adjustedPos.x / cellSize;
   int verticalCell = adjustedPos.y / cellSize;

   //determine if both dimensions are within the bounds of the nav mesh
   if (horizontalCell < horizontal && verticalCell < vertical)
   {
      return Vector2Int(horizontalCell, verticalCell);
   }
   else
   {
      return Vector2Int(0, 0);
   }
}

NavPath NavMesh::GetPathToPoint(Vector2Int origin, Vector2Int destination)
{
   return GetPathToPoint(GetCell(origin), GetCell(destination));
}

NavPath NavMesh::GetPathToPoint(Cell* origin, Cell* destination)
{
   if (origin != destination && origin != nullptr && destination != nullptr)
   {
      if (!origin->GetOverlapData().AnyOverlaps() && !destination->GetOverlapData().AnyOverlaps())
      {
         //create a priority queue for the frontier, and create dictionary to map cells to pathfinding data
         std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>> frontier = std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>>();
         std::unordered_map<Cell*, CellData> data = std::unordered_map<Cell*, CellData>();

         //push the start node to the data
         data.emplace(origin, CellData(origin, origin, 0, EstDist(destination->GetCellCoordinate() - origin->GetCellCoordinate())));
         origin->SetParent(origin);

         //add the starting element to the frontier
         frontier.push(data.find(origin)->second);

         //as long as the frontier has cells to visit
         while (frontier.size() > 0)
         {
            //check that top isn't destination
            if (frontier.top().mSelf != destination)
            {
               //copy next in queue, then pop from queue
               CellData top = frontier.top();
               frontier.pop();

               //generate neighbors from top
               PushNeighbors(top, destination, frontier, data);
            }
            else break;
         }

         //make a path
         std::list<Cell*> path = std::list<Cell*>();

         //if there's a frontier to backtrack from
         if (frontier.size() > 0)
         {
            //until the origin is reached
            std::cout << data.size() << std::endl << std::endl;
            frontier.top().mSelf->SetParent(frontier.top().mParent);
            Cell* it = frontier.top().mSelf;
            while (it != nullptr)
            {
               if (it->GetParent() != it)
               {
                  //add the cell to the front of the path, the increment the iterator
                  //std::cout << it->GetCellCoordinate() << std::endl;
                  path.push_front(it);
                  it = it->GetParent();
               }
               //if the parent of the current cell is itself, the origin has been reached
               else
               {
                  break;
               }
            }
         }

         //constructor a nav path from the data and return it
         NavPath pathToReturn = NavPath(path);
         pathToReturn.DrawPath();
         return pathToReturn;
      }
      else
      {
         return NavPath();
      }
   }
   else
   {
      return NavPath();
   }
}

bool NavMesh::IsValidCell(Vector2Int tileCoords)
{
   return (tileCoords >= Vector2Int(0, 0) && tileCoords < Vector2Int(horizontal, vertical));
}

void NavMesh::PushNeighbors(CellData cellData, Cell* dest, std::priority_queue<CellData, std::vector<CellData>, std::greater<CellData>>& inFrontier, std::unordered_map<Cell*, CellData>& inData)
{
   //create cell iterator
   Cell* it;
   CellData dataToAdd;

   //for each direction to search
   for (int i = 0; i < NEIGHBOR_COUNT; i++)
   {
      //check if there's a valid cell in the direction
      it = GetCell(cellData.mSelf->GetCellCoordinate() + NEIGHBOR_DIR[i]);
      if (it != nullptr)
      {
         //check that the cell has no collisions
         if (!it->GetOverlapData().AnyOverlaps())
         {
            //check if the data map already contains a weight
            if (inData.contains(it))
            {
               //generate the cell data to add
               dataToAdd = CellData(it, cellData.mSelf, cellData.mG + 1, EstDist(dest->GetCellCoordinate() - it->GetCellCoordinate()));

               //check if should replace current
               auto loc = inData.find(it);
               if (dataToAdd < loc->second)
               {
                  loc->second = dataToAdd;
                  inFrontier.push(loc->second);
                  it->SetParent(cellData.mSelf);
               }
            }
            else
            {
               //if there's no data, add this to the data map and the frontier
               dataToAdd = CellData(it, cellData.mSelf, cellData.mG + 1, EstDist(dest->GetCellCoordinate() - it->GetCellCoordinate()));
               inData.emplace(it, dataToAdd);
               inFrontier.push(dataToAdd);
               it->SetParent(cellData.mSelf);
            }
         }
      }
   }
}

void NavMesh::RegisterObstacle(Obstacle* inObstacle)
{
   //add this obstacle to the obstacle list
   obstacles.push_back(inObstacle);
}