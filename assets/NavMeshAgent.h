#ifndef NAVMESHAGENT_H
#define NAVMESHAGENT_H

#include "Navmesh.h"
#include <raylib.h>
/*
* Used this forum thread to figure out how to delay the program for a certain amount of time
* https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
*/
#include <chrono>
#include <thread>

class NavMeshAgent
{
public:
	NavMeshAgent(NavPath& currentPath);
	void draw();
	void MoveAgent();
	NavPath& GetPath();

private:
	NavPath* path;
	Vector2 center;
	float radius;
	Color color = PINK;
};


#endif
