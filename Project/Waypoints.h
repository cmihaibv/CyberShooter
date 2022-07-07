#pragma once
#include "Waypoint.h"
#include <vector>

class Waypoints
{
public:
	Waypoints();
	~Waypoints();

	void UpdateWaypoint();
	void AddWaypoint(float xcoord, float ycoord, float zcoord);
	XMFLOAT3& GetCurrentCoords();

	std::vector<Waypoint> m_waypoints;
private:
	
	int m_numWaypoints;
	int m_waypointIndex;
	XMFLOAT3 m_currentCoords;

};