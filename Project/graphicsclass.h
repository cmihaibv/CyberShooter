#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include <windows.h>
#include "Renderer.h"
#include "Object.h"
#include "buffer.h"
#include "Camera.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();
	Renderer* m_D3DXRenderer;
	Object* m_Model;
	Buffer* m_ColorShader;
	CameraClass* m_Camera;

};

#endif