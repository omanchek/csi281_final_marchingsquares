#include "NavData.h"
#include "raylib.h"

NavPath::NavPath()
{
   pathNodes = std::list<Cell*>();
}

NavPath::NavPath(std::list<Cell*> initPath)
{
   //cycle through list and copy cells
   for (Cell* it : initPath)
   {
      pathNodes.push_back(it);
   }
}

NavPath::~NavPath()
{

}

void NavPath::AddCell(Cell* newCell)
{
   //add the new node to the back of the path
   pathNodes.push_back(newCell);
}

void NavPath::ClearPath()
{
   pathNodes.clear();
}

void NavPath::DrawPath()
{
   //create iterators
   Cell* oneBehind = nullptr;
   Vector2 c1, c2;

   //for each node
   for (Cell* it : pathNodes)
   {
      //check if both nodes are valid
      if (it != nullptr && oneBehind != nullptr)
      {
         c1 = oneBehind->GetCenter();
         c2 = it->GetCenter();
         DrawLine(c1.x, c1.y, c2.x, c2.y, DARKGREEN);
      }

      //increment oneBehind
      oneBehind = it;
   }
}

Cell* NavPath::GetFront()
{
   if (pathNodes.size() > 0)
   {
      return pathNodes.front();
   }
   else
   {
      return nullptr;
   }
}

Cell* NavPath::GetBack()
{
   if (pathNodes.size() > 0)
   {
      return pathNodes.back();
   }
   else
   {
      return nullptr;
   }
}

void NavPath::GetNext()
{
    // Checks if the size of the path list is greater than zero
    if (pathNodes.size() > 0)
    {
        // If so, pops the head of the list so that the next cell becomes the head
        pathNodes.pop_front();
    }
}

int NavPath::GetSize()
{
   return pathNodes.size();
}

bool NavPath::RemoveFront()
{
   //check any nodes
   if (pathNodes.size() > 0)
   {
      pathNodes.pop_front();
      return true;
   }
   else
   {
      return false;
   }
}