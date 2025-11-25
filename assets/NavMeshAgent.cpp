#include "NavMeshAgent.h"
//#include "NavData.h"

// sets the path for the Agent
NavMeshAgent::NavMeshAgent(NavPath& currentPath)
{
	// Sets the agent's path to the path set by the NavData
	path = &currentPath;

	// Sets the center to the center of the first cell in the list
	center = path->GetFront()->GetCenter();
	// Sets the radius of the circle to 5
	radius = 5;
}

void NavMeshAgent::draw()
{
	// Draws the circle on the screen
	DrawCircle(center.x, center.y, radius, color);
}

void NavMeshAgent::MoveAgent()
{
	// Calls the GetNext function
	path->GetNext();
	// Checks if the size of the path is greater than zero
	if (path->GetSize() > 0)
	{
		// If so, cets the center of the path the new front
		center = path->GetFront()->GetCenter();
	}

	// Pauses the call by 100 milliseconds
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

NavPath& NavMeshAgent::GetPath()
{
	// returns the current path
	return *path;
}