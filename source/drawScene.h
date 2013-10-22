#ifndef __drawScene__
#define __drawScene__

#include "matStack.h"

// Global variables
extern float gCurrentTime;
extern float gLastTime;
extern float gDeltaTime;

void drawScene(float time);
void initScene(int width, int height);
void setColour(float c1,float c2,float c3);
void useTexture(int v);
void useLighting(int t);

void drawCube(ModelviewStack & mvs);
void drawSquare(ModelviewStack & mvs);
void drawCylinder(ModelviewStack & mvs);
void drawCone(ModelviewStack & mvs);
void drawSphere(ModelviewStack & mvs);

#endif
