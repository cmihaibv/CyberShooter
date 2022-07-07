#include "Waypoints.h"

Waypoints::Waypoints()
{
	m_numWaypoints = 0;
}

Waypoints::~Waypoints()
{
}

void Waypoints::UpdateWaypoint()
{
	m_waypointIndex = (m_waypointIndex + 1) % m_numWaypoints;
	m_currentCoords = m_waypoints[m_waypointIndex].GetCoords();
}

void Waypoints::AddWaypoint(float xcoord, float ycoord, float zcoord)
{
	Waypoint wp;
	wp.SetCoords(xcoord, ycoord, zcoord);
	m_waypoints.push_back(wp);
	m_numWaypoints = m_waypoints.size();
}

XMFLOAT3& Waypoints::GetCurrentCoords()
{
	return m_currentCoords = m_waypoints[m_waypointIndex].GetCoords();
}
