#ifndef PATH_H
#define PATH_H

#include <vector>
#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Transform.h"

using std::vector;

class Path
{
private:
	vector<IGameObject*> _nodes;
	vector<vec3> _points;
	vector<vec3> _tangents;
	vector<vec3> _finalPoints;
	vector<double> _distances;
	Transform _transform;

public:
	Path();
	~Path();

	vector<IGameObject*> GetNodes() { return _nodes; }
	vector<vec3> GetPoints() { return _finalPoints; }

	void AddNode(IGameObject* node);
	void RemoveNode(IGameObject* node);

	void CalculatePath();
	void CalculatePathOrig();

	void DrawDebugSpheres(ModelviewStack* ms);

};

#endif
