#include "Obstacle.h"

Obstacle::Obstacle()
{
   numVerts = 0;
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
}

Obstacle::~Obstacle()
{
   //clean up vertex list
   delete verts;
}

void Obstacle::DrawBoundingBox()
{
   //draw whatever is stored in bounding box
   DrawRectangleLines(boundingBox.GetBottomLeft().x, boundingBox.GetTopRight().y, boundingBox.GetWidth(), boundingBox.GetHeight(), PINK);
}

void Obstacle::DrawObstacle()
{
   //create iterator
   int i;

   //for each point
   for (i = 0; i < numVerts - 1; i++)
   {
      //draw a line from this point to the next
      DrawLine(verts[i].x, verts[i].y, verts[i + 1].x, verts[i + 1].y, RED);
   }

   //draw final line
   DrawLine(verts[i].x, verts[i].y, verts[0].x, verts[0].y, RED);
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
      false;
   }
}