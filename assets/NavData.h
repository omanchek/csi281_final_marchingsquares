#ifndef NAVDATA_H
#define NAVDATA_H

#include "Cell.h"
#include <list>

class NavPath
{
   public:
      NavPath();
      ~NavPath();

      void AddCell(Cell& newCell);
      Cell& GetFront();
      Cell& GetBack();
      bool RemoveFront();

   private:
      std::list<Cell> pathNodes;
};

#endif
