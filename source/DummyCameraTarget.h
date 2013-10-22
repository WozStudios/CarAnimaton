#ifndef DUMMY_CAMERA_TARGET_H
#define DUMMY_CAMERA_TARGET_H

class DummyCameraTarget : public IGameObject
{
private:
	vec3 _position;

public:
	DummyCameraTarget(vec3 position = vec3()) { _position = position; }

	vec3 GetPosition() { return _position; }
	void SetPosition(vec3 position) { _position = position; }
};

#endif