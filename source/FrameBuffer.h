#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "opengl.h"
#include "global.h"

class FrameBuffer
{
private:
	GLuint _id;
	GLuint _textureId;
	GLuint _depthBufferId;

	GLuint _vao;

public:
	FrameBuffer() {}
	~FrameBuffer();

	void Init(int width, int height);

	GLuint GetId() { return _id; }
	GLuint GetTextureId() { return _textureId; }
	GLuint GetDepthBufferId() { return _depthBufferId; }

	void CheckStatus();
	void Draw();

	static void UseFrameBuffer(GLuint id) { glBindFramebuffer(GL_FRAMEBUFFER, id); }

private:
	void SetupQuad();
};

#endif