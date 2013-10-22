//
//  global.h
//  cse3431Template
//
//  Created by Petros Faloutsos on 9/29/13.
//  Copyright (c) 2013 Petros Faloutsos. All rights reserved.
//

#ifndef cse3431Template_global_h
#define cse3431Template_global_h

#include <stdio.h>
#include "FrameSaver.h"

#ifndef __APPLE__
#include <string>
#endif

// SET THIS VARIABLE!!!!
#ifdef WIN32
const std::string gProjectPath = "../" ;
#else
const std::string gProjectPath = "/Users/pfal/courses/cse3431/cse3431Template-glfw3-v19/" ;
#endif

const int MAX_STACK_SIZE = 100; // the maximum size of the modelview stack

// Path for shader;
const std::string gShaderDir = gProjectPath + "shaders/";
// Path for saving frames
const std::string gFrameDir = gProjectPath + "frames/" ;

// global variables -- In practice they would in a singlenton
extern FrameSaver gFrameSaver;
extern int gAnimate;
extern int gRecording;
extern int gWidth;
extern int gHeight;
extern float gTime;

void instructions(void);

#endif
