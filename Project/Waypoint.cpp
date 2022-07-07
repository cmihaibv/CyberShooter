#include "Waypoint.h"

void Waypoint::SetCoords(float x,float y, float z)
{
	m_coords.x = x;
	m_coords.y = y;
	m_coords.z = z;
}

XMFLOAT3& Waypoint::GetCoords()
{
	return m_coords;
}
