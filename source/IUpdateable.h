#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

class IUpdateable
{
public:
	virtual void Update(float time) = 0;
};

#endif