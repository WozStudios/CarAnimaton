//========================================================================
// This is a small test application for GLFW.
// The program opens a window (640x480), and renders a spinning colored
// triangle (it is controlled with both the GLFW timer and the mouse).
// Author: Petros Faloutsos
//========================================================================

#include <stdio.h>
#include <stdlib.h>

#include "opengl.h"
#include "global.h"
#include "drawScene.h"

#include "FrameSaver.h"

void instructions(void) ;
void useLighting(int t) ;

using namespace std ;


// global variables -- In practice they would in a singlenton

static FrameSaver gFrameSaver;
static int gAnimate = 0;
static int gRecording = 0;
static int gWidth = 500 ;
static int gHeight = 500 ;
static float gTime = 0.0 ;

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



// Used during initialization of GLFW
static void error_callback(int error, const char* description)
{
    std::cerr << description;

}

// Callback that handles mouse motion interaction
static void mouseMotion_callback(GLFWwindow* window, double x, double y)
{
    //cerr << "Curson is now at " << x << " " << y << endl ;
    return ;
        
}

// Callback that handles mouse button interaction
static void mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        cerr << "Left Button Pressed\n" ;
        
    }
    
}

// Callback that handles keyboard interaction
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return ;
    }
    
    if( action == GLFW_PRESS )
    {
        switch (key) {
            case GLFW_KEY_V :
                gFrameSaver.DumpPPM(gWidth,gHeight) ;
                break;
            case GLFW_KEY_A: // toggle animation

                gAnimate = 1 - gAnimate ;
                cerr << "Animate = " << gAnimate << endl ;
                // reset the timer to point to the current time
                glfwSetTime(gTime) ;

                break ;
            case GLFW_KEY_T:
                // reset time
                gTime = 0.0 ;
                //reset your objects here (call a function)
                
                break ;
            case GLFW_KEY_M:
              
                if( gRecording == 1 )
                {
                    cerr << "Frame recording disabled." << endl;
                    gRecording = 0 ;
                    gFrameSaver.StopRecord() ;
                    glfwSetTime(gTime) ;

                }
                else
                {
                    cerr << "Frame recording enabled." << endl;
                    gRecording = 1;
                    gFrameSaver.StartRecord() ;
                }
                break;
            case GLFW_KEY_L:
                if( GLFW_MOD_SHIFT & mods ) useLighting(0) ;
                else useLighting(1) ;
                break ;
            case GLFW_KEY_H:
                instructions();
                break;
        }
    }
    
}

// Callback that handles resizing of the OpenGL window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



// The main entry point of the program
int main( void )
{
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback) ;
    glfwSetMouseButtonCallback(window, mouseButton_callback) ;
    glfwSetCursorPosCallback(window, mouseMotion_callback) ;
    
    
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
        
        // store time in a global variable
        if( gRecording && gAnimate )
        {
            gFrameSaver.DumpPPM(gWidth,gHeight) ;
            gTime += 0.033 ; // 30 FPS
        }
        else if( gAnimate)
            gTime = glfwGetTime();
        
        if( gAnimate) {
            
            // Handle events
            glfwPollEvents() ;
        }
        else {
            glfwWaitEvents() ;
        }
       
    }

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

