#include "Vector2Int.h"

Vector2Int::Vector2Int()
{
   x = 0; y = 0;
}
Vector2Int::Vector2Int(int inX, int inY)
{
   x = inX; y = inY;
}

bool Vector2Int::operator>=(const Vector2Int& rhs)
{
   return (x >= rhs.x && y >= rhs.y);
}

bool Vector2Int::operator<(const Vector2Int& rhs)
{
   return (x < rhs.x && y < rhs.y);
}

void Vector2Int::operator=(const Vector2Int& rhs)
{
   x = rhs.x; y = rhs.y;
}

Vector2Int Vector2Int::operator-(const Vector2Int& rhs)
{
   return Vector2Int(x - rhs.x, y - rhs.y);
}

bool operator==(const Vector2Int& lhs, const Vector2Int& rhs)
{
   return (lhs.x == rhs.x && lhs.y == rhs.y);
}

Vector2Int operator+(const Vector2Int& lhs, const Vector2Int& rhs)
{
   return Vector2Int(lhs.x + rhs.x, lhs.y + rhs.y);
}

std::ostream& operator<<(std::ostream& lhs, const Vector2Int& rhs)
{
   lhs << "(" << rhs.x << ", " << rhs.y << ")";
   return lhs;
}