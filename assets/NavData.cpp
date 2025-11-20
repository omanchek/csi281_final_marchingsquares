#include "NavData.h"

NavPath::NavPath()
{
   pathNodes = std::list<Cell>();
}

NavPath::~NavPath()
{

}

void NavPath::AddCell(Cell& newCell)
{
   //add the new node to the back of the path
   pathNodes.push_back(newCell);
}

Cell& NavPath::GetFront()
{
   return pathNodes.front();
}

Cell& NavPath::GetBack()
{
    return pathNodes.back();
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