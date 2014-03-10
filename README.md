Assignment02
============

A 'Free Animation' assignment for Intro to Computer Graphics course.

This is a short animation I made for my Introduction to Computer Graphics course.  It was created using OpenGL/C++.  

Note: None of the models were made in an external modeling package. 
Everything is modeled out of primitive shapes- cubes, planes, spheres, and cylinders. 
This was part of the requirements of the assignment.

Libraries used:

GLEW- extension loading
GLFW- windowing, input
GLM- vector/matrix math
SFML- audio playback.

Audio tools: Ableton Live, Native Instruments Komplete

|-----------------------------------------------------------|

I've uploaded a rendered video to YouTube:
http://youtu.be/UTJO5Wc7sfw

If you have any questions, please let me know:
email: woz.studios@gmail.com

|-----------------------------------------------------------|

Controls for navigating the scene:
==================================
| W - Forward
| A - Strafe Left
| S - Back
| D - Strafe Right
| Q - Down
| E - Up
|
| MouseLeft Click - Rotate Camera (Note: at the moment, 
|			free rotation doesn't work quite correctly,
|			due to the way it behaves during the animation)
|
| Space(Hold) - Increase camera movement speed by x2
|
| P - Begin animation 
|
|-----------------------------------------------------------|

I sorted the project into several filters in Visual Studio.  All exisiting code went into the Engine filter.
There is a filter for interfaces, a filter for GameObjects, and finally a filter called Game, 
which is basically all the other logic/utility code.

==========
Interfaces
==========
IGameObject - Implemented by all objects that are instantiated in the Scene.  Has functions for getting/setting
		Transform attributes.

IDrawable - Implemented by all objects that are drawn.
		Has one Draw function that accepts a pointer to a modelviewStack.

IUpdateable - Implemented by all animated objects.
		Has one Update function that accepts the time passed in seconds from the last frame.

====
Game
====
Scene - Main container for all GameObjects in the scene.
	Each frame, iterates over all gameobjects, and updates and draw them as needed.

AnimationManager - holds a pointer to all objects used in the main animation.
		Controls entire animation, mainly based off of triggers from camera location.

Generators - There are a few generators that all function fairly similar to one another.
		They generate objects with several random/predefined attributes, and passes them to the Scene.

Camera - Main camera object.  Scene passes its locaiton to SetViewMatrix().
	It also holds a DummyCameraTarget, which is passed as the target to SetViewMatrix(), and is used for animating 
	the camera movement.

FPSCounter - Displays FPS in console window.

FrameBuffer - Sadly, never actually used in application.  It is a wrapper for OpenGL Framebuffers, for post-processing,
	but I did not have enough time to actually use it.

MathUtils - contains math constants, such as PI, radians/degrees conversions, as well as interpolation functions.

Path - Animation path used for the cars and for the camera (through DummyCameraTarget).

Node - Single keyframe in a Path. The path then cubicly interpolates the inbetween points.

Parametric - Holds parametric functions which are passed into a Bird as a function pointer.
	Used as the paths for the birds.

Random - Functions that return random numbers within a range.

Textures - Holds macros for all textures used.

Utility - Contains an optimization function, isVisible(), that calculates whether an object is within view of the camera.


|-----------------------------------------------------------|

I feel as though most of the GameObjects are pretty self-explanatory.  The draw functions are usually 
commented to describe which part of the object is currently being drawn.

Here a few special ones:
------------------------ 

Car - An abstract class inherited by SmallCar and SportsCar.

Billboard - A 2D square that is always facing the camera.  Used for the trees.

ElectricalBox - In addition to itself, it also creates the sparks used in its explosion.

Skybox - 5 squares that form an inside-out cube, always centered around the camera

|-----------------------------------------------------------|
