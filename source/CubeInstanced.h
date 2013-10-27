#ifndef CUBE_INSTANCED_H
#define CUBE_INSTANCED_H

#include "opengl.h"
#include "geomObjects.h"

class CubeInstanced : Object
{
public:
	CubeInstanced() { return; }
	CubeInstanced::CubeInstanced(std::string name, GLuint prog);
	void SetBuffers(GLuint prog);
	void Draw();
};

#endif