#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Waypoint
{
public:

	void SetCoords(float x, float y, float z);
	XMFLOAT3& GetCoords();

private:
	XMFLOAT3 m_coords;

};