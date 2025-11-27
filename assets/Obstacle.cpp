#include "Obstacle.h"

#include<iostream>

Obstacle::Obstacle()
{
   numVerts = 0;
   verts = nullptr;
}

Obstacle::Obstacle(const Vector2 vertexList[], int vertices)
{
   //init the vert list
   verts = new Vector2[vertices];

   //copy the vertex count
   numVerts = vertices;

   //copy all of the data over
   for (int i = 0; i < numVerts; i++)
   {
      verts[i] = vertexList[i];
   }

   //run bounding box calculations based on vertices inputted
   CalculateBoundingBox();
}

Obstacle::Obstacle(std::vector<Vector2> vertexList)
{
   //store the number of vertices being inputted
   numVerts = vertexList.size();

   //init the container for the vertices
   verts = new Vector2[numVerts];

   //copy over the data
   for (int i = 0; i < numVerts; i++)
   {
      verts[i] = vertexList[i];
   }

   //run the bounding box calculations
   CalculateBoundingBox();
}

Obstacle::~Obstacle()
{
   //clean up vertex list   
   delete[] verts;
   std::cout << "OBSTACLE VERTICES DELETED SUCCESSFULLY" << std::endl << std::endl;
}

OverlapData Obstacle::CheckCollisionOfCell(Square& inSquare)
{
   OverlapData overlaps = OverlapData();

   //check if each point is inside the shape or not
   overlaps.bLeft = CheckPointInsideShape(inSquare.GetBottomLeft(), false);
   overlaps.bRight = CheckPointInsideShape(inSquare.GetBottomRight(), false);
   overlaps.tLeft = CheckPointInsideShape(inSquare.GetTopLeft(), true);
   overlaps.tRight = CheckPointInsideShape(inSquare.GetTopRight(), false);

   //return the overlap data
   return overlaps;
}

bool Obstacle::CheckPointInsideShape(Vector2 point, bool debugPrint)
{
   //create a tracker for number of hits
   int hits = 0;

   //for each segment in the shape
   for (int i = 0; i < numVerts; i++)
   {
      //check if it's the last point, and therefore should wrap
      if (i == numVerts - 1)
      {
         if (RaycastSegment(point, i, 0)) hits++;
      }
      else
      {
         if (RaycastSegment(point, i, i + 1)) hits++;
      }
   }

   //once all raycast have been done, eval the result and return (even hits = not inside, odd hits = inside)

   if (hits % 2 == 1)
   {
      return true;
   }
   else
   {
      return false;
   }
}

void Obstacle::DrawBoundingBox()
{
   //draw whatever is stored in bounding box
   DrawRectangleLines(boundingBox.GetBottomLeft().x, boundingBox.GetTopRight().y, boundingBox.GetWidth(), boundingBox.GetHeight(), BLUE);
}

void Obstacle::DrawObstacle()
{
   //create iterator
   int i;

   //for each point
   for (i = 0; i < numVerts - 1; i++)
   {
      //draw a line from this point to the next
      DrawLine(verts[i].x, verts[i].y, verts[i + 1].x, verts[i + 1].y, BLUE);
   }

   //draw final line
   DrawLine(verts[i].x, verts[i].y, verts[0].x, verts[0].y, BLUE);
}

bool Obstacle::CalculateBoundingBox()
{
   //check any points to use
   if (numVerts > 0)
   {
      //initialize trackers for bounding box and populate with basic data
      Vector2 bottomLeft, topRight;
      bottomLeft = topRight = verts[0];

      //loop through all vertices to adjust best data
      for (int i = 0; i < numVerts; i++)
      {
         //update bottom left
         bottomLeft.x = std::min(verts[i].x, bottomLeft.x);
         bottomLeft.y = std::max(verts[i].y, bottomLeft.y);

         //update top right
         topRight.x = std::max(verts[i].x, topRight.x);
         topRight.y = std::min(verts[i].y, topRight.y);
      }

      //return the final square of the bounding box
      boundingBox = Square(bottomLeft, topRight);
      return true;
   }
   else
   {
      return false;
   }
}

bool Obstacle::InBetween(float value, float bound1, float bound2)
{
   //check what order the bounds are in
   if (bound1 <= bound2)
   {
      if (value >= bound1 && value <= bound2)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      if (value >= bound2 && value <= bound1)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
}

bool Obstacle::RaycastSegment(Vector2 origin, int first, int second)
{
   //first determine the slope and offset (i.e. linear equation of the segment)
   float xDif, yDif, slope, offset;
   xDif = verts[second].x - verts[first].x;
   yDif = verts[second].y - verts[first].y;
   slope = yDif / xDif;
   offset = verts[first].y - (slope * verts[first].x);

   //if vertical line
   if (xDif == 0)
   {
      return (InBetween(origin.y, verts[first].y, verts[second].y) && verts[first].x >= origin.x);
   }

   else
   {
      //determine when there is an intersection
      float xIntersect = (origin.y - offset) / slope;

      //return if the intersect is valid
      return (InBetween(xIntersect, verts[first].x, verts[second].x) && xIntersect >= origin.x);
   }
}