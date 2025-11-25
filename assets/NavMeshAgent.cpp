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
	path->GetNext();
	if (path->GetSize() > 0)
	{
		center = path->GetFront()->GetCenter();
	}
}

NavPath& NavMeshAgent::GetPath()
{
	// returns the current path
	return *path;
}