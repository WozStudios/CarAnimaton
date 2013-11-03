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

		/* If the dot product is 1, the angle is 0.  
		 * This causes a glitch below, so we just exit true here. */
		if (dotProduct > 0.999 && dotProduct < 1.001)
			return true;

		double angle = acos(dotProduct);
		double halfPI = 0.5 * M_PI;
		return angle < halfPI && angle > -halfPI;
	}
};
#endif