//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480), and renders a spinning colored
// triangle (it is controlled with both the GLFW timer and the mouse).
// Author: Petros Faloutsos
//========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "opengl.h"
#include "global.h"
#include "drawScene.h"

#include "FrameSaver.h"

#include "InputManager.h"

// global variables -- In practice they would in a singlenton
FrameSaver gFrameSaver;
int gAnimate = 0;
int gRecording = 0;
int gWidth = 500;
int gHeight = 500;
float gTime = 0.0;

void instructions(void) ;
void useLighting(int t) ;

using namespace std ;

// Initialize OopenGL
void initOpenGL(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    
    glEnable(GL_DEPTH_TEST) ;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

// Function that prints OpenGL context information
void printOpenGLVersion(GLFWwindow *window)
{
    // obtain the OpenGL version information
    const GLubyte* openGLversion = glGetString(GL_VERSION);
    const GLubyte* openGLvendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION) ;
    
    int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR) ;
    int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) ;
        
    GLint texSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texSize);
    
    
    printf("OpenGL Vendor: %s\n", openGLvendor ) ;
    printf("Renderer: %s\n",  renderer) ;
    printf("OpenGL Version (string): %s\n",  openGLversion) ;
    printf("OpenGL Version (integer) : %d.%d\n", major, minor) ;
    printf("GLSL Version: %s\n", glslVersion) ;
    printf("Maximum Texture Size %d\n", texSize) ;
}

// Callback that handles resizing of the OpenGL window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Used during initialization of GLFW
void error_callback(int error, const char* description)
{
    std::cerr << description;
}

// The main entry point of the program
int main( void )
{
    srand((unsigned)time(0));

    glfwSetErrorCallback(error_callback) ;

    // Initialise GLFW
    if( !glfwInit() )
    {
        std::cerr <<  "Failed to initialize GLFW\n" ;
        exit( EXIT_FAILURE );
    }

    // Open a window and create its OpenGL context
    //glfwDefaultWindowHints() ;
#ifdef __APPLE__ // 3.2 for the current OSX
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2) ;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE) ;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) ;
#else // 4.3 for windows and linux

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4) ;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3) ;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE) ;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE) ;
#endif
    
    GLFWwindow* window = glfwCreateWindow(gWidth, gHeight, "CSE 3431", NULL, NULL);
    if( !window )
    {
        std::cerr << "Failed to open GLFW window\n";
        
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwMakeContextCurrent(window);
    
    //glfwSwapInterval(0) ;
    checkError() ;
    
    // Load the OpenGL function pointers
    glewExperimental = GL_TRUE ;
    GLenum errGlew = glewInit();
    if (GLEW_OK != errGlew)
    {
        std::cerr << "ERROR: Cannot initialize glew\n" ;
        fprintf(stderr, "Error: %s\n", glewGetErrorString(errGlew));
        glfwDestroyWindow(window);
        glfwTerminate();
        exit( EXIT_FAILURE );
    }
    fprintf(stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    
    // Set event callbacks so we can capture and handle user interaction
    glfwSetKeyCallback(window, InputManager::key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback) ;
    glfwSetMouseButtonCallback(window, InputManager::mouseButton_callback) ;
    glfwSetCursorPosCallback(window, InputManager::mouseMotion_callback) ;
    
    printOpenGLVersion(window) ;
    
    // Initialize OpenGL
    initOpenGL() ;
    
    // Initialize the scene (e.g. load primitives etc)
    initScene(gWidth, gHeight) ;
    
    // Set the recording directory
    gFrameSaver.SetDir(gFrameDir) ;
    
    // global variable that keems the master clock
    gTime = 0.0 ;
    // Start the main loop until an event closes the window
    while (!glfwWindowShouldClose(window))
    {
        //cerr << gTime << endl ;
    
        // draw the scene
        drawScene(gTime) ;
           
        // Swap buffers
        glfwSwapBuffers(window);
        
        if(gRecording)
        {
            gFrameSaver.DumpPPM(gWidth,gHeight) ;
            gTime += 0.033 ; // 30 FPS
        }
      
        // store time in a global variable
        gTime = glfwGetTime();

        glfwPollEvents() ;
    }

    InputManager::DeleteInstance();

    // Destroy the window to free resources
    glfwDestroyWindow(window);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    exit( EXIT_SUCCESS );
}

void instructions(void)
{
    cerr << "Keyboard:" << endl;
    cerr << "  v to save the image." << endl;
    cerr << "  t to reset time and objects." << endl;
    cerr << "  a to toggle the animation." << endl;
    cerr << "  m to toggle frame dumping." << endl;
    cerr << " l/L to turn lighting on/off." << endl ;
    cerr << "  ESC to quit" << endl;
    
    cerr << endl;
}