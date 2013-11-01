#include "FrameBuffer.h"
#include "glm/glm.hpp"
#include "matStack.h"
#include "drawScene.h"

using glm::vec3;
using glm::vec4;

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &_id);
	glDeleteTextures(1, &_textureId);
}

void FrameBuffer::Init(int width, int height)
{
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenTextures(1, &_depthBufferId);
	glBindTexture(GL_TEXTURE_2D, _depthBufferId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenFramebuffers(1, &_id);
	glBindFramebuffer(GL_FRAMEBUFFER, _id);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureId, 0);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBufferId, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	CheckStatus();	

	SetupQuad();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;

	glEnable(GL_DEPTH_TEST) ;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glViewport( 0, 0, width, height );
	// Clear color buffer to blue
	glClearColor( 0.0f, 1.0f, 1.0f, 1.0f );
	useLighting(1);

	setMaterial(vec3(0.2f,0.2f,0.2f), vec3(1.f,0.f,0.f),vec3(1.0f,1.0f,1.f), 20.0)  ;
	setLight(vec4(0.f,0.f,100.f,1.f), vec3(1.0f,1.0f,1.0f), vec3(1.0f,1.0f,1.0f),vec3(1.0f,1.0f,1.0f))  ;

}

void FrameBuffer::SetupQuad()
{
	GLfloat vertices[18] = { -1.0f, -1.0f, 0.0f, 
						      1.0f, -1.0f, 0.0f, 
						      1.0f,  1.0f, 0.0f, 
						     -1.0f, -1.0f, 0.0f, 
						      1.0f,  1.0f, 0.0f, 
						     -1.0f,  1.0f, 0.0f };
	
	GLfloat texCoords[12] = { 0.0f, 0.0f, 
						      1.0f, 0.0f, 
						      1.0f, 1.0f, 
						      0.0f, 0.0f, 
						      1.0f, 1.0f, 
						      0.0f, 1.0f };

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLuint positionAttribute = glGetAttribLocation(gShaders.getActiveID(), "VertexPosition");
	glEnableVertexAttribArray(positionAttribute);
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint texCoordBuffer;
	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	GLuint texCoordAttribute = glGetAttribLocation(gShaders.getActiveID(), "VertexTexCoord");
	glEnableVertexAttribArray(texCoordAttribute);
	glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	checkError();
}

void FrameBuffer::CheckStatus()
{
	if (glCheckFramebufferStatus(_id) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Failed to create FrameBuffer\n";
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void FrameBuffer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	GLuint texUniform = glGetUniformLocation(gShaders.getActiveID(), "renderedTexture");
	if ((int) texUniform >=0)
		glUniform1i(texUniform, 0) ;

	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0) ;
}