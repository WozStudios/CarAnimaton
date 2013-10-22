#ifndef IDRAWABLE_H
#define IDRAWABLE_H

#include "MatStack.h"

class IDrawable
{
public:
	virtual void Draw(ModelviewStack* ms) = 0;
};

#endif