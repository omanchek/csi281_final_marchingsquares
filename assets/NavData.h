#ifndef NAVDATA_H
#define NAVDATA_H

#include "Cell.h"
#include <list>
#include <algorithm>

class NavPath
{
   public:
      NavPath();
      NavPath(std::list<Cell*> initPath);
      ~NavPath();

      void AddCell(Cell* newCell);
      void DrawPath();
      Cell* GetFront();
      Cell* GetBack();
      void GetNext();
      int GetSize();
      bool RemoveFront();

   private:
      std::list<Cell*> pathNodes;
};

#endif
