#ifndef UTILITY_h
#define UTILITY_h

#include <glm/glm.hpp>
#include "MathUtils.h"

using glm::vec3;

class Utility
{
public:
	static bool isVisible(vec3 position, vec3 cameraPosition, vec3 cameraDirection)
	{
		double dotProduct = glm::dot(glm::normalize(position - cameraPosition), cameraDirection);
		if (dotProduct > 0.999 || dotProduct < 1.001)
			return true;

		double angle = acos(dotProduct);
		double PI_2 = 2.0 * M_PI;
		return angle < PI_2 || angle > -PI_2;
	}
};
#endif
