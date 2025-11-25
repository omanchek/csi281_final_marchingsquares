#include "NavMeshAgent.h"
//#include "NavData.h"

// sets the path for the Agent
NavMeshAgent::NavMeshAgent(NavPath& currentPath)
{
	// Sets the agent's path to the path set by the NavData
	path = &currentPath;

	center = path->GetFront()->GetCenter();
	radius = 5;
}

void NavMeshAgent::draw()
{
	DrawCircle(center.x, center.y, radius, color);
}

void NavMeshAgent::MoveAgent()
{
   while (path->RemoveFront() != false)
	{
		path->RemoveFront();
	}
}

NavPath& NavMeshAgent::GetPath()
{
	// returns the current path
	return *path;
}