#include "InputManager.h"
#include "global.h"
#include "drawScene.h"

using std::cout;
using std::endl;

InputManager* InputManager::Instance = NULL;

InputManager::InputManager()
{
	_mousePosX = 0.0;
	_mousePosY = 0.0;
	
	_isLeftClicked = false;
	_isRightClicked = false;

	_isSpacePressed = false;
}

InputManager* InputManager::GetInstance()
{
	if (Instance == NULL)
		Instance = new InputManager();

	return Instance;
}

void InputManager::DeleteInstance()
{
	if (Instance != NULL)
	{
		delete Instance;
		Instance = NULL;
	}
}

// Callback that handles mouse motion interaction
void InputManager::mouseMotion_callback(GLFWwindow* window, double x, double y)
{
	InputManager* inputManager = InputManager::GetInstance();
	inputManager->SetMousePosX(x);
	inputManager->SetMousePosY(gHeight - y);

	//cout << "MousePos: (" << inputManager->GetMousePosX() << ", " << inputManager->GetMousePosY() << ")\n";

    return;
}

// Callback that handles mouse button interaction
void InputManager::mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* inputManager = NULL;
	
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		inputManager = InputManager::GetInstance();
		inputManager->SetLeftClicked(true);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		inputManager = InputManager::GetInstance();
		inputManager->SetLeftClicked(false);
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		inputManager = InputManager::GetInstance();
		inputManager->SetRightClicked(true);
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		inputManager = InputManager::GetInstance();
		inputManager->SetRightClicked(false);
    }
}

// Callback that handles keyboard interaction
void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* inputManager = NULL;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return ;
    }
    
    if( action == GLFW_PRESS)
    {
        switch (key)
		{
		case GLFW_KEY_V:
            gFrameSaver.DumpPPM(gWidth,gHeight);
            break;

        case GLFW_KEY_A: // toggle animation
            gAnimate = 1 - gAnimate;
            cout << "Animate = " << gAnimate << endl;
            // reset the timer to point to the current time
            glfwSetTime(gTime);
            break;
			
		case GLFW_KEY_T:
            // reset time
            gTime = 0.0;
            //reset your objects here (call a function)
            break;

        case GLFW_KEY_M:
            if(gRecording == 1)
            {
                cout << "Frame recording disabled." << endl;
                gRecording = 0;
                gFrameSaver.StopRecord();
                glfwSetTime(gTime);
            }
            else
            {
                cout << "Frame recording enabled." << endl;
                gRecording = 1;
                gFrameSaver.StartRecord();
            }
            break;

        case GLFW_KEY_L:
            if(GLFW_MOD_SHIFT & mods) useLighting(0);
            else useLighting(1);
            break;

        case GLFW_KEY_H:
            instructions();
            break;

		case GLFW_KEY_SPACE:
			inputManager = InputManager::GetInstance();
			inputManager->SetSpacePressed(true);
			break;
        }
    }

	if( action == GLFW_RELEASE)
    {
        switch (key)
		{
		case GLFW_KEY_SPACE:
			inputManager = InputManager::GetInstance();
			inputManager->SetSpacePressed(false);
			break;
        }
    }
}