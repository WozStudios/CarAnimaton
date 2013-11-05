#include "Path.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Node.h"

void Path::Destroy()
{
	for (vector<IGameObject*>::iterator i = _nodes.begin(); i != _nodes.end(); i++)
	{
		delete *i;
	}
};

void Path::AddNode(IGameObject* node)
{
	_nodes.push_back(node);
}

void Path::RemoveNode(IGameObject* node)
{
	for (vector<IGameObject*>::iterator i = _nodes.begin(); i != _nodes.end(); i++)
	{
		if (*i == node)
			_nodes.erase(i);
	}
}

void Path::CalculatePathOrig()
{
	//double c;
	//double pathLength = 0.0;
	//
	//for (int i = 1; i < _nodes.size() - 2; i++)
	//{
	//	double distance = glm::length(_nodes[i]->GetPosition() - _nodes[i + 1]->GetPosition());
	//	double increment = 1.0 / distance;
	//	c = 0.0;
	//	for (int j = 0; j < (int)distance; j++, c += increment)
	//	{
	//		vec3 p0 = _nodes[i - 1]->GetPosition();
	//		vec3 p1 = _nodes[i]->GetPosition();
	//		vec3 p2 = _nodes[i + 1]->GetPosition();
	//		vec3 p3 = _nodes[i + 2]->GetPosition();
	//
	//		double x = cubicInterpolate(p0.x, p1.x, p2.x, p3.x, c);
	//		double y = cubicInterpolate(p0.y, p1.y, p2.y, p3.y, c);
	//		double z = cubicInterpolate(p0.z, p1.z, p2.z, p3.z, c);
	//
	//		_points.push_back(new Node(vec3(x, y, z)));
	//
	//		if (_points.size() > 1)
	//		{
	//			int index = _points.size() - 1;
	//			pathLength += glm::length(_points[index]->GetPosition() - _points[index - 1]->GetPosition());
	//		}
	//	}
	//}
	//
	//double stepSize = pathLength / _points.size();
	//
	//
	//std::cout << "Total path length: " << pathLength << "\n";
}

void Path::CalculatePath()
{
	double c;
	double pathLength = 0.0;
	int numPoints = 1000;


	for (int i = 1; i < _nodes.size() - 2; i++)
	{
		double distance = glm::length(_nodes[i]->GetPosition() - _nodes[i + 1]->GetPosition());
		double increment = 1.0 / distance;
		c = 0.0;
		for (int j = 0; j < (int)distance; j++, c += increment)
		{
			vec3 p0 = _nodes[i - 1]->GetPosition();
			vec3 p1 = _nodes[i]->GetPosition();
			vec3 p2 = _nodes[i + 1]->GetPosition();
			vec3 p3 = _nodes[i + 2]->GetPosition();

			double x = cubicInterpolate(p0.x, p1.x, p2.x, p3.x, c);
			double y = cubicInterpolate(p0.y, p1.y, p2.y, p3.y, c);
			double z = cubicInterpolate(p0.z, p1.z, p2.z, p3.z, c);

			_points.push_back(vec3(x, y, z));
			int index = _points.size() - 1;

			if (index == 0)
				_distances.push_back(0.0);

			if (index > 0)
			{
				vec3 tangent = _points[index] - _points[index - 1];
				_tangents.push_back(glm::normalize(tangent));
				pathLength += glm::length(tangent);
				_distances.push_back(pathLength);
			}
		}
	}

	float currentDistance = 0.0f;
	float stepSize = 0.14;
	int numFinalPoints = pathLength / stepSize;

	int index = 0;
	_finalPoints.push_back(_points[index]);

	vec3 lastPoint = _points[index];

	for (int i = 0; i < numFinalPoints; i++)
	{
		vec3 newPoint = lastPoint + stepSize * _tangents[index];
		_finalPoints.push_back(newPoint);
		currentDistance += glm::length(newPoint - lastPoint);
		lastPoint = newPoint;

		while (index < _distances.size() - 1 && currentDistance > _distances[index + 1])
			index++;
	}

	std::cout << "Total path length: " << pathLength << "\n";
}

void Path::DrawDebugSpheres(ModelviewStack* ms)
{
	useTexture(0);
	setColour(1.0f, 0.0f, 0.0f);
	for (vector<IGameObject*>::iterator i = _nodes.begin(); i != _nodes.end(); i++)
	{
		ms->Push();
		{
			ms->Translate((*i)->GetPosition());
			ms->Scale(vec3(0.5f, 0.5f, 0.5f));

			drawSphere(*ms);
		}
		ms->Pop();
	}

	setColour(0.0f, 0.0f, 1.0f);
	//for (vector<vec3>::iterator i = _points.begin(); i != _points.end(); i++)
	//{
	//	ms->Push();
	//	{
	//		ms->Translate((*i));
	//		ms->Scale(vec3(0.25f, 0.25f, 0.25f));
	//
	//		drawSphere(*ms);
	//	}
	//	ms->Pop();
	//}

	setColour(0.0f, 1.0f, 0.0f);
	int index = 0;
	for (vector<vec3>::iterator i = _finalPoints.begin(); i != _finalPoints.end(); i++, index++)
	{
		if (index % 10 == 0)
		{
			ms->Push();
			{
				ms->Translate((*i));
				ms->Scale(vec3(0.35f, 0.35f, 0.35f));

				drawSphere(*ms);
			}
			ms->Pop();
		}
	}
}