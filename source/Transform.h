#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

using glm::vec3;

struct  Transform
{
	vec3 position;
	vec3 rotation;
	vec3 scale;

	Transform()
	{
		position = vec3();
		rotation = vec3();
		scale = vec3(1.0, 1.0, 1.0);
	}
};

#endif