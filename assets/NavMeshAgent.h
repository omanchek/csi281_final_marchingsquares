#ifndef NAVMESHAGENT_H
#define NAVMESHAGENT_H

#include "Navmesh.h"
#include <raylib.h>

class NavMeshAgent
{
public:
	NavMeshAgent(NavPath& currentPath);
	void draw();
	void MoveAgent();
	NavPath& GetPath();

private:
	NavPath* path;
	NavMesh navMesh;
	float centerX;
	float centerY;
	float radius;
	Color color;
};


#endif
