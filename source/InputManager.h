#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "opengl.h"
#include <map>

using std::map;

#define DEAD_ZONE 2.5

class InputManager
{
private:
	static InputManager* Instance;

	map<int, bool> _keys;
	
	double _mousePosX;
	double _mousePosY;

	double _mouseScroll;

	double _lastMousePosX;
	double _lastMousePosY;
	
	bool _isLeftClicked;
	bool _isRightClicked;
	
	bool _isSpacePressed;
	bool _wasSpacePressed;

	bool _wasPPressed;

	bool _isTPressed;
	bool _wasTPressed;

	GLFWwindow* _window;

public:
	double GetMousePosX() { return _mousePosX; }
	double GetMousePosY() { return _mousePosY; }

	void SetMousePosX(double x) { _lastMousePosX = _mousePosX; _mousePosX = x; }
	void SetMousePosY(double y) { _lastMousePosY = _mousePosY; _mousePosY = y; }

	double GetMouseScroll() { return _mouseScroll; }
	void SetMouseScroll(double mouseScroll) { _mouseScroll = mouseScroll; }
	
	double GetMouseDX();
	double GetMouseDY();

	bool IsLeftClicked() { return _isLeftClicked; }
	void SetLeftClicked(bool isLeftClicked) { _isLeftClicked = isLeftClicked; }
	
	bool IsRightClicked() { return _isRightClicked; }
	void SetRightClicked(bool isRightClicked) { _isRightClicked = isRightClicked; }
	
	bool WasSpacePressed() { return _wasSpacePressed; }
	void SetSpacePressed(bool wasSpacePressed) { _wasSpacePressed = wasSpacePressed; }

	bool WasPPressed() { return _wasPPressed; }
	void SetPPressed(bool wasPPressed) { _wasPPressed = wasPPressed; }

	//bool WasSpacePressed() { return _wasSpacePressed; }
	//void WasSpacePressed(bool wasSpacePressed) { _wasSpacePressed = wasSpacePressed; }
	
	bool IsKeyPressed(int key) { return glfwGetKey(_window, key) == GLFW_PRESS; }

	void SetWindow(GLFWwindow* window) { _window = window; }

	void Clear();
	void ClearKeys() { _keys.clear(); }

	static InputManager* GetInstance();
	static void DeleteInstance();

	// Callbacks
	static void mouseMotion_callback(GLFWwindow* window, double x, double y);
	static void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseScroll_callback(GLFWwindow* window, double xOffset, double yOffset);

private:
	InputManager();
	void Init();
};

#endif