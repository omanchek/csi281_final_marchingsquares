#ifndef VECTOR2INT_H
#define VECTOR2INT_H

struct Vector2Int
{
   int x, y;

   Vector2Int();
   Vector2Int(int inX, int inY);

   bool operator>=(const Vector2Int& rhs);
   bool operator<(const Vector2Int& rhs);
   void operator=(const Vector2Int& rhs);
   Vector2Int operator-(const Vector2Int& rhs);
};

//general functions
bool operator==(const Vector2Int& lhs, const Vector2Int& rhs);
Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs);

#endif