#ifndef __drawScene__
#define __drawScene__

#include "matStack.h"

// Global variables
extern float gCurrentTime;
extern float gLastTime;
extern float gDeltaTime;

void drawScene(float time);
void initScene(int width, int height);
void deleteScene();
void setColour(float c1,float c2,float c3);
void setMaterial(glm::vec3 Ka, glm::vec3 Kd, glm::vec3 Ks, float shininess);
void useTexture(int v);
void useLighting(int t);

void drawCube(ModelviewStack & mvs);
void drawSquare(ModelviewStack & mvs);
void drawCylinder(ModelviewStack & mvs);
void drawCone(ModelviewStack & mvs);
void drawSphere(ModelviewStack & mvs);

#endif
