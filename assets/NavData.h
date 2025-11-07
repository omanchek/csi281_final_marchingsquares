#ifndef NAVDATA_H
#define NAVDATA_H

#include <list>
#include "Cell.h"

class NavPath
{
   public:
      NavPath();
      ~NavPath();

      void AddCell(Cell& newCell);
      Cell& GetFront();
      bool RemoveFront();

   private:
      std::list<Cell> pathNodes;
};

#endif
