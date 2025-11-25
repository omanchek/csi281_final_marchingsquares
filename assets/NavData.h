#ifndef NAVDATA_H
#define NAVDATA_H

#include "Cell.h"
#include <list>

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
      Cell* GetNext();
      int GetSize();
      bool RemoveFront();

   private:
      std::list<Cell*> pathNodes;
};

#endif
