#include "NavMeshAgent.h"

// sets the path for the Agent
NavMeshAgent::NavMeshAgent(NavPath& currentPath)
{
	// Sets the agent's path to the path set by the NavData
	*path = currentPath;

	centerX = 200;
	centerY = 200;
	radius = 5;
	color = GREEN;

	DrawCircle(centerX, centerY, radius, color);
}

void NavMeshAgent::MoveAgent()
{
	while (path->RemoveFront() != false)
	{
		navMesh.GetPathToPoint(path->GetFront(), path->GetBack());
		path->RemoveFront();
	}
}

NavPath& NavMeshAgent::GetPath()
{
	// returns the current path
	return *path;
}