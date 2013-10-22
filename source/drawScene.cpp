

// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "opengl.h"
#include "global.h"
#include "image.h"
#include "drawScene.h"



#include "program.h"
#include "geomObjects.h"

#include "MatStack.h"

using glm::vec3 ;
using glm::vec4 ;
using glm::mat4 ;

// -------- global variables -- Normally they should be in a singleton or namespace

// The shader list
static Shaders gShaders ;
// The canonical objects (primitives) ;
static Square *gSquare;
static Cube *gCube ;
static Cylinder *gCylinder ;
static Cone *gCone ;
static Sphere *gSphere ;

static bool gUsingLighting ;
static bool gUsingTextures ;
static glm::mat4 gProjMat(1.0f) ;
static glm::mat4 gMVP(1.0f) ;


// The modeling matrix stack
static ModelviewStack gMS(MAX_STACK_SIZE) ;

const GLuint gNumTex = 3;
GLuint gTexIDs[gNumTex] ; // Three textures


void loadTextures(void) ;



void printMat4(glm::mat4 &m)
{
    printf("------------------\n") ;
    for( int i = 0 ; i < 4; i++)
    {
        for( int j = 0 ; j < 4; j++)
            printf("%lf ", m[i][j]) ;
        printf("\n") ;
    }
}

void setMaterial(glm::vec3 Ka, glm::vec3 Kd, glm::vec3 Ks, float shininess)
{
    gShaders.setFloat3("Material.Ka", Ka[0], Ka[1], Ka[2]);
    gShaders.setFloat3("Material.Kd", Kd[0], Kd[1], Kd[2]);
    gShaders.setFloat3("Material.Ks", Ks[0], Ks[1], Ks[2]);
    gShaders.setFloat("Material.Shininess", shininess);
}

void setLight(glm::vec4 Position, glm::vec3 Ia, glm::vec3 Id, glm::vec3 Is)
{
    gShaders.setFloat3("Light.Ia", Ia[0], Ia[1], Ia[2]);
    gShaders.setFloat3("Light.Id", Id[0], Id[1], Id[2]);
    gShaders.setFloat3("Light.Is", Is[0], Is[1], Is[2]);
    gShaders.setFloat4("Light.Position", Position[0], Position[1], Position[2], Position[3]);
}

void setColour(float c1,float c2,float c3)
{
	// Ks always one for non metalic materials
	vec3 ks = vec3(1.0f) ;
    vec3 c(c1,c2,c3) ;
	setMaterial(0.1f*c,c,ks ,20.0f) ;
}


// Tells the fragment shader which of the 3 textures to use:
// 0 means no texture
// 1,2,3 specifies the respective texture
// 12 means 1 and 2
// 23 means 2 and 3
// 13 means 1 and 3
// 123 means all three
void useTexture(int v)
{
    gShaders.setInt("useTex", v) ;
    if(v) gUsingTextures = true ;
    else gUsingTextures = false ;
    
}

void useLighting(int t) // should be 0 or 1
{
    gShaders.setInt("useLighting", t) ;
    if(t) gUsingLighting = true ;
    else gUsingLighting = false ;
}

// Sets the Modelview, the normal, and the  MVP matrices from the stack given
void setMatricesFromStack(ModelviewStack & mvs)
{
    glm::mat4 m = mvs.Top() ;
    gShaders.setMatrix4f("modelviewMat", m);
    checkError();
    
    gMVP = gProjMat*m ;
    gShaders.setMatrix4f("MVP", gMVP) ;
    
    glm::mat4 nm  = glm::inverseTranspose(m);
    gShaders.setMatrix4f("normalMat", nm);
    checkError();
    
}


// Utility function that draws a 2x2x2 cube center at the origin
// Sets the modelview matrix at the "modelviewMat" uniform of gProg1
// and the corresponding "normalMat"
void drawCube(ModelviewStack & mvs)
{
        setMatricesFromStack(mvs) ;
        gCube->Draw() ;
}


// Utility function that draws a 1x1 quad center at the origin
// Sets the modelview matrix and the normal matrix of gProg1
void drawSquare(ModelviewStack & mvs)
{
    setMatricesFromStack(mvs) ;
    gSquare->Draw() ;
    
}

// Utility function that draws a cylinder along z of height 1 centered at the origin
// and radius 0.5 ;
// Sets the modelview matrix and the normal matrix of gProg1
void drawCylinder(ModelviewStack & mvs)
{
    
    setMatricesFromStack(mvs) ;
    gCylinder->Draw() ;
    
}

// Utility function that draws a cone along z of height 1 centered at the origin
// and base radius 1.0 ;
// Sets the modelview matrix and the normal matrix of gProg1
void drawCone(ModelviewStack & mvs)
{
    
    setMatricesFromStack(mvs) ;
    gCone->Draw() ;
    
}

// Draws a unit sphere centered at the origin of radius 1.0 ;
// Sets the modelview matrix and the normal matrix of gProg1
void drawSphere(ModelviewStack & mvs)
{
    
    setMatricesFromStack(mvs) ;
    gSphere->Draw() ;
    
}


// Scene initialization -- Put here things that need to be done only once
// before the scene is drawn
void initScene(int width, int height)
{
    glViewport( 0, 0, width, height );
    // Clear color buffer to black
    glClearColor( 0.5f, 0.5f, 0.2f, 1.0f );
    
    
    checkError() ;
    gShaders.setShaderDir(gShaderDir) ;
    
    // Load the shader pairs -- MUST BE DONE before the objects are loaded
    checkError() ;
    

    gShaders.loadShaderPair("diffuse") ;
   // gShaders.loadShaderPair("simple") ;
    
    checkError() ;
    gShaders.use(0) ; // this number is the index in the list not the progam id
    
    checkError() ;
    loadTextures() ;
    checkError() ;
    
    // Load canonical primitives (objects)
    GLuint pid = gShaders.getActiveID() ;
    
    checkError() ;
    gSquare = new Square("square1", pid) ;
    checkError() ;
    gCube = new Cube("cube1", pid) ;
    gCylinder = new Cylinder("cylinder1", 20, pid) ;
    gCone = new Cone("cone1", 20,  pid) ;
    gSphere = new Sphere("sphere1", 20, pid) ;
    
    // set the global projection matrix
    //gProjMat = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
    gProjMat = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, -500.0f, 500.0f);
    //printMat4(gProjMat) ;
    
    useLighting(1) ;
    useTexture(3) ;
    glm:mat4 m(1.0f );
    gShaders.setMatrix4f("modelviewMat", m);
    gShaders.setMatrix4f("normalMat", m);
   // gShaders.setMatrix4f("projMat", gProjMat);
   // gShaders.setFloat("time", time);
    
    setMaterial(vec3(0.2f,0.2f,0.2f), vec3(1.f,0.f,0.f),vec3(1.0f,1.0f,1.f), 20.0)  ;
    setLight(vec4(0.f,0.f,100.f,1.f), vec3(0.1f,0.1f,0.1f), vec3(1.0f,1.0f,1.0f),vec3(1.0f,1.0f,1.0f))  ;

    
}

// The main display function
// Put your drawing code here  - Feel free to add functions as you see fit
void drawScene(float time)
{
    
    gShaders.use(0) ;
    //gShaders.setFloat("time", time);
    
    //printf("Time = %f\n", time) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // Load an identity matrix on the modeling stack
    gMS.LoadIdentity();
    
    //------------ Set up a view --------------
    
    //gMS.Rotate(10.0f,vec3(0.f,1.f,0.f)) ;
    //gMS.Rotate(10.0f,vec3(1.f,0.f,0.f)) ;
    gMS.SetViewMatrix(vec3(5,5,10),vec3(0,0,0), vec3(0,1,0));
    
    //------------- Draw your objects ----------
  
  
   // setColour(1.0,0.0,0.0) ;
 
    useTexture(1) ;
    setColour(1.0,1.0,1.0) ; // When using textures you may want to set the color to
                             // white cause the shader multiplies it with the texture
    gMS.Push() ;
    {
        gMS.Translate((vec3(6.0f,0.0f,0.0f))) ;
        gMS.Rotate(10*time, vec3(0.0f,1.0f,0.0f)) ;
       
        drawSquare(gMS) ;
    }
    gMS.Pop() ;
  
  
    useTexture(3) ;
    setColour(1.0,1.0,1.0) ;
    gMS.Push() ;
    {
        gMS.Translate((vec3(-4.0f,0.0f,0.0f))) ;
        gMS.Rotate(10*time, vec3(0.0f,1.0f,0.0f)) ;
        drawSphere(gMS) ;
    }
    gMS.Pop() ;
  

    useTexture(2) ;
    setColour(1.0,1.0,1.0) ;
    gMS.Push();
    {
        gMS.Translate((vec3(-1.0f,0.0f,0.0f))) ;
        gMS.Rotate(time*10,vec3(0.f,1.f,0.f) );
        drawCube(gMS) ;
    }
    gMS.Pop() ;
    
    useTexture(0) ;
    setColour(1.0,1.0,0.0) ;
    gMS.Push();
    {
        gMS.Translate((vec3(2.0f,0.0f,0.0f))) ;
        gMS.Rotate(time*10,vec3(0.f,1.f,0.f) );
        drawCone(gMS) ;
    }
    gMS.Pop() ;
    
    
    useTexture(0) ;
    setColour(0.8,0.2,0.0) ;
    gMS.Push();
    {
        gMS.Translate((vec3(4.0f,0.0f,0.0f))) ;
        gMS.Rotate(time*10,vec3(0.f,1.f,0.f) );
        drawCylinder(gMS) ;
    }
    gMS.Pop() ;

    
}


void initTexture()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
}

void setTexture(GLuint prog, std::string uname, GLuint activeTexID)
{
    initTexture() ;
    GLuint texUniform = glGetUniformLocation(prog, uname.c_str()) ;
    if ((int) texUniform >=0) {
        glUniform1i(texUniform, activeTexID) ;
    }
    else {
        std::cerr << "Shader did not contain the uniform " << uname  << std::endl;
	}
}

void loadTextures(void)
{
    
    std::string fname = gProjectPath + "media/" + "sunset.bmp" ;
    char fname_char[200] ;
    strcpy(fname_char, fname.c_str()) ;
    GL_Image2D Img1(fname_char) ;
    fname = gProjectPath + "media/" + "floor.bmp" ;
    strcpy(fname_char, fname.c_str()) ;
    GL_Image2D Img2(fname_char) ;
   
    glGenTextures(gNumTex,gTexIDs) ;
    
    glActiveTexture(GL_TEXTURE0) ;
    glBindTexture(GL_TEXTURE_2D,gTexIDs[0]) ;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Img1.m_width,
                 Img1.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 Img1.m_data);
    setTexture(gShaders.getActiveID(),"texture1", 0) ;
    
    
    glActiveTexture(GL_TEXTURE1) ;
    glBindTexture(GL_TEXTURE_2D,gTexIDs[1]) ;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Img2.m_width,
                 Img2.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 Img2.m_data);
    setTexture(gShaders.getActiveID(),"texture2", 1) ;

    
    glActiveTexture(GL_TEXTURE2) ;
    glBindTexture(GL_TEXTURE_2D,gTexIDs[2]) ;
    int i, j, c;
    GLubyte checkImage[64][64][4] ;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            c = ((((i&0x8)==0)^((j&0x8))==0))*255;
            checkImage[i][j][0] = (GLubyte) c;
            checkImage[i][j][1] = (GLubyte) c;
            checkImage[i][j][2] = (GLubyte) c;
            checkImage[i][j][3] = (GLubyte) 255;
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64,
                 64, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 checkImage);
    setTexture(gShaders.getActiveID(), "texture3", 2) ;
    
  
}

