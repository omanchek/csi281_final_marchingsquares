#ifndef NAVMESHAGENT_H
#define NAVMESHAGENT_H

#include "Navmesh.h"
#include <raylib.h>
/*
bames53. “Answer to ‘How do you add a timed delay to a C++ program?’” Stack Overflow, 17 Mar. 2012,
   https://stackoverflow.com/a/9747668.

   used this forum thread to figure out how to delay the program for a certain amount of time
*/
#include <chrono>
#include <thread>

class NavMeshAgent
{
public:
	NavMeshAgent(NavPath& currentPath, Vector2 centerBail);
	void draw();
	void MoveAgent();
   Vector2 GetCenter() { return center; }
	NavPath& GetPath();
   void SetCenter(Vector2 pos) { center = pos; }
   void Stop();

private:
	NavPath* path;
	Vector2 center;
	float radius;
	Color color = BLUE;
};


#endif
