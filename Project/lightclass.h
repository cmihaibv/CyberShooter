#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <DirectXMath.h>

using namespace DirectX;

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	XMVECTOR GetDiffuseColor();
	XMVECTOR GetDirection();

private:
	XMVECTOR m_diffuseColor;
	XMVECTOR m_direction;
};

#endif