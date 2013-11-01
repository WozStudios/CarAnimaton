///////////////////////////////////////////////////////////////////////////////
// 
// testing vertex array (glDrawElements, glDrawArrays)
//
//  Original AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
//  Changes and additions: Petros Faloutsos 2013
// CREATED: 2005-10-04
// UPDATED: 2012-07-11
///////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#include <windows.h>
#endif

#include "opengl.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "glm/glm.hpp"

#include "image.h"

#include "program.h"

#include "geomObjects.h"

#include "MathUtils.h"

using std::stringstream;
using std::cout;
using std::endl;
using std::ends;

using namespace glm ;

// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).
GLfloat vertices1[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                       -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                        1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                       -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                       -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                       -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                        1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                       -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

// normal array
GLfloat normals1[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
                        0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

                        1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                       -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
                       -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

                        0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
                        0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

                        0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
                        0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4

// color array
GLfloat colors1[]   = { 1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v1-v2 (front)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,      // v2-v3-v0

                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v0-v3-v4 (right)
                        0, 0, 0,   0, 0, 0,   0, 0, 0,      // v4-v5-v0

                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                        1, 1, 0,   1, 1, 0,   1, 1, 0,      // v1-v6-v7 (left)
                        1, 1, 0,   1, 1, 0,   1, 1, 0,      // v7-v2-v1

                        0, 1, 1,   0, 1, 1,   0, 1, 1,      // v7-v4-v3 (bottom)
                        0, 1, 1,   0, 1, 1,   0, 1, 1,      // v3-v2-v7

                        0, 0, 1,   0, 0, 1,   0, 0, 1,      // v4-v7-v6 (back)
                        0, 0, 1,   0, 0, 1,   0, 0, 1 };    // v6-v5-v4

GLfloat cubeTexCoord[] = { 1,1,  0,1, 0,0,      // v0-v1-v2 (front)
    0,0,   1,0,   1, 1,      // v2-v3-v0
    
    0, 1,   0,0,  1,0,      // v0-v3-v4 (right)
    1,0,   1, 1,   0,1,      // v4-v5-v0
    
    1, 0,   1, 1,  0, 1,      // v0-v5-v6 (top)
    0, 1,   0, 0,  1, 0,      // v6-v1-v0
    
    1, 1,   0, 1,  0,0,     // v1-v6-v7 (left)
    0,0,    1,0,   1, 1,      // v7-v2-v1
    
    0,1,   0,0,   1,0,      // v7-v4-v3 (bottom)
    1,0,   1,1,    0,1,  // v3-v2-v7
    
    0,0, 1,0, 1,1,     // v4-v7-v6 (back)
    1,1, 0,1, 0,0 };    // v6-v5-v4

// color array
GLfloat colors2[]   = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
    1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0
    
    1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
    0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0
    
    1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
    0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0
    
    1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
    0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1
    
    0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
    1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7
    
    0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
    0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

using namespace std;

// Retrieves the locations of the folloing attributes:
// "position", "colour", "normal", "VertexTexCoord"
void Object::getAttributeLocations(GLuint prog,
                                   GLuint &positionAttribute,
                                   GLuint &normalAttribute,
                                   GLuint &colorAttribute,
                                   GLuint &texCoordAttribute)
{
    // Get attribute locations
   
    positionAttribute = glGetAttribLocation(prog, "VertexPosition");
    if ((int) positionAttribute < 0) {
        cerr << "Shader did not contain the 'VertexPosition' attribute." << endl;
    }
    
    colorAttribute = glGetAttribLocation(prog, "VertexColour");
    if ((int) colorAttribute < 0) {
        cerr << "Object::getAttributeLocations: Shader did not contain the 'VertexColour' attribute." << endl;
    }
    
    normalAttribute = glGetAttribLocation(prog, "VertexNormal");
    if ((int) normalAttribute < 0) {
        cerr << "Shader did not contain the 'VertexNormal' attribute." << endl;
    }
    
    texCoordAttribute = glGetAttribLocation(prog, "VertexTexCoord");
    if ((int) texCoordAttribute < 0) {
        cerr << "Shader did not contain the 'VertexTexCoord' attribute." << endl;
    }
    
}

void Square::SetBuffers(GLuint prog){
    
    VertexData vertexData[4] = {
        { vec4(-0.5f, -0.5f, 0.0f, 1.0f ), vec4( 1.0f, 0.0f, 0.0f, 1.0f ), vec3(0.0f,0.0f,1.0f), vec2(0.0f,0.0f) },
        { vec4( 0.5f, -0.5f, 0.0f, 1.0f ), vec4( 0.0f, 1.0f, 0.0f, 1.0f ), vec3(0.0f,0.0f,1.0f), vec2(1.0f,0.0f) },
        { vec4( 0.5f,  0.5f, 0.0f, 1.0f ), vec4( 0.0f, 0.0f, 1.0f, 1.0f ), vec3(0.0f,0.0f,1.0f), vec2(1.0f,1.0f) },
        { vec4(-0.5f,  0.5f, 0.0f, 1.0f ), vec4( 1.0f, 1.0f, 1.0f, 1.0f ), vec3(0.0f,0.0f,1.0f), vec2(0.0f,1.0f) }
    };
 
    GLuint colourAttribute, positionAttribute, normalAttribute, texCoordAttribute;

    checkError() ;
    getAttributeLocations(prog, positionAttribute, normalAttribute, colourAttribute, texCoordAttribute) ;
    checkError() ;
    glGenBuffers(1, &_vbo);
    checkError() ; 
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    //populate the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexData), vertexData, GL_STATIC_DRAW);
    checkError() ;
    glGenVertexArrays(1, &_vao);
     checkError() ;
    glBindVertexArray(_vao);
     checkError() ;
    glEnableVertexAttribArray(positionAttribute);  
    checkError() ;
    glEnableVertexAttribArray(colourAttribute);  
    checkError() ;
    glEnableVertexAttribArray(normalAttribute);  
    checkError() ;
    glEnableVertexAttribArray(texCoordAttribute);  
    checkError() ;
   
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo) ; // bind the vbo that contains the attributes
   
    
    glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *)0);
    glVertexAttribPointer(colourAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) sizeof(vec4));
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4)));
    glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4) + sizeof(vec3)));
    glBindVertexArray(0) ;
    
}

Square::Square(std::string name, GLuint prog)
{
    SetBuffers(prog) ;
    return ;
}

void Square::Draw(void) {
    //checkError() ;
    glFrontFace(GL_CCW) ;
    //checkError() ;
    glDisable(GL_CULL_FACE) ;
    //checkError() ;
    glBindVertexArray(_vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //checkError() ;
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    //checkError() ;
    glBindVertexArray(0) ;
    //checkError() ;
}

Cube::Cube(std::string name, GLuint prog)
{
    SetBuffers(prog) ;
    return ;
}

void Cube::SetBuffers(GLuint prog)
{
    
    checkError() ;
    
    // put all elements in one array

    
    VertexData vertexDataArray[36] ;
    
    int count = 0, texCount = 0 ;
    for( int i = 0 ; i < 36; i++){
        vertexDataArray[i].position[0] = vertices1[count] ;
        vertexDataArray[i].position[1] = vertices1[count+1] ;
        vertexDataArray[i].position[2] = vertices1[count+2] ;
        vertexDataArray[i].position[3] = 1.0 ;
        
        
        vertexDataArray[i].normal[0] = normals1[count] ;
        vertexDataArray[i].normal[1] = normals1[count + 1] ;
        vertexDataArray[i].normal[2] = normals1[count + 2] ;
        
        vertexDataArray[i].colour[0] = colors1[count] ;
        vertexDataArray[i].colour[1] = colors1[count + 1] ;
        vertexDataArray[i].colour[2] = colors1[count + 2] ;
        vertexDataArray[i].colour[3] = 1.0 ;
        
        
        vertexDataArray[i].texCoord[0] = cubeTexCoord[texCount] ;
        vertexDataArray[i].texCoord[1] = cubeTexCoord[texCount+1] ; ;
        
        
        //cout << vertexDataArray[i].position << " --- " << vertices1[count] << ","
        //    << vertices1[count+1] << "," << vertices1[count+2] << endl ;
        //cout << vertexDataArray[i].position << "-- "
        //<< vertexDataArray[i].colour << endl ;
        count = count + 3 ;
        texCount = texCount + 2 ;
        
    }
    
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);  checkError() ;
    glBufferData(GL_ARRAY_BUFFER, 36*sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
    
    
    GLuint colourAttribute, positionAttribute, normalAttribute, texCoordAttribute;
    getAttributeLocations(prog, positionAttribute, normalAttribute, colourAttribute, texCoordAttribute) ;
    
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    checkError() ;
    glEnableVertexAttribArray(positionAttribute);
    glEnableVertexAttribArray(colourAttribute);
    glEnableVertexAttribArray(normalAttribute) ;
    glEnableVertexAttribArray(texCoordAttribute) ;
    checkError() ;
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo) ; // bind the vbo containing the attributes
    glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *)0);
    glVertexAttribPointer(colourAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) sizeof(vec4));
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4)));
    //glVertexAttrib2f(texCoordAttribute,0.f,1.f) ;
    glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4) + sizeof(vec3)));
    
    checkError() ;
    glBindVertexArray(0) ;
    //cout << sizeof(VertexData) / (float) sizeof(GLfloat) << endl ;
    
}

void Cube::Draw(void) {

    glFrontFace(GL_CCW) ;
    glCullFace(GL_BACK);
    
    glEnable(GL_CULL_FACE) ;
    //glDisable(GL_CULL_FACE) ;
    
    glBindVertexArray(_vao);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0) ;
    
}

Cylinder::Cylinder(std::string name, int n, GLuint prog)
{
    if( n < 1) return ;
    _n = n ;
    SetBuffers(prog) ;
    return ;
}

bool flip(const VertexData &vd1,const VertexData &vd2, const VertexData &vd3){

    // compute average normal
    vec3 an = 1.0f/3.0f*(vd1.normal + vd2.normal + vd3.normal) ;
    // compute from triangle
    vec3 va = vd2.normal - vd1.normal ;
    vec3 vb = vd3.normal - vd1.normal ;
    vec3 tn = glm::cross(vb,va) ;
    if( dot(an,tn) < 0) return true ;
    
    return false ;
}

void GetVertexCylinder(VertexData &vd, float u, float v)
{
    
    vd.position[0] = 0.5*cos(u*2*M_PI);
    vd.position[1] = 0.5*sin(u*2*M_PI) ;
    vd.position[2] = (v-0.5) ;
    vd.position[3] = 1.0 ;
    
    vd.normal[0] = cos(u*2*M_PI) ;
    vd.normal[1] = sin(u*2*M_PI) ;
    vd.normal[2] = 0.0 ;
    vd.colour = vec4(1.0,0.0,0.0,1.0) ;
    
    vd.texCoord[0] = u ;
    vd.texCoord[1] = v ;
    
    return;
}

void Cylinder::SetBuffers(GLuint prog){ 
    
    if( _n < 1) return;
    
    VertexData *vertexDataArray = new VertexData[_n*_n*6] ;
    
    checkError() ;
    
    float du = 1.0 / (float) _n ;
    float dv = du ;
    // do it by quads made up of two triangles
    int count = 0 ;
    for( float u = 0 ; u < 1.0 ; u += du) {
        for( float v = 0 ; v < 1.0  ; v += dv) {
            //cerr << "----------------------------\n" ;
            //cerr << "(" << u << "," << v << ")" << endl ;
            //cerr << "(" << u+du << "," << v << ")" << endl ;
            //cerr << "(" << u+du << "," << v+dv << ")" << endl ;
            //cerr << "(" << u << "," << v+dv << ")" << endl ;
           
            // make them into triangles
            VertexData vd1,vd2,vd3,vd4 ;
            GetVertexCylinder(vd1, u,v) ;
            GetVertexCylinder(vd2, u+du,v) ;
            GetVertexCylinder(vd3, u+du,v+dv) ;
            GetVertexCylinder(vd4, u,v+dv) ;
            
            
            vertexDataArray[count++] = vd1 ;
            vertexDataArray[count++] = vd2 ;
            vertexDataArray[count++] = vd3 ;
            
           
            vertexDataArray[count++] = vd3 ;
            vertexDataArray[count++] = vd4 ;
            vertexDataArray[count++] = vd1 ;
            
            
           
        }
        
        
        GLuint colourAttribute, positionAttribute, normalAttribute, texCoordAttribute;
        getAttributeLocations(prog, positionAttribute, normalAttribute, colourAttribute, texCoordAttribute) ;
        
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);  checkError() ;
        // load the attribute data into the vbo
        glBufferData(GL_ARRAY_BUFFER, _n*_n*6*sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
        checkError() ;
        
        glEnableVertexAttribArray(positionAttribute);
        glEnableVertexAttribArray(colourAttribute);
        glEnableVertexAttribArray(normalAttribute) ;
        glEnableVertexAttribArray(texCoordAttribute) ;
        
        checkError() ;
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); // bind the vdo containing the attributes
        glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *)0);
        glVertexAttribPointer(colourAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) sizeof(vec4));
        glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4)));
        glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4) + sizeof(vec3)));

        checkError() ;
        glBindVertexArray(0) ;
        //cout << sizeof(VertexData) / (float) sizeof(GLfloat) << endl ;
        
    }
}

void Cylinder::Draw() {
    
    glFrontFace(GL_CCW) ;
    //glEnable(GL_CULL_FACE) ;
    glDisable(GL_CULL_FACE) ;
    
    glBindVertexArray(_vao);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0,_n*_n*6 );
    //checkError() ;
    glBindVertexArray(0) ;
    
}

Cone::Cone(std::string name, int n, GLuint prog)
{
    if( n < 1) return ;
    _n = n ;
    SetBuffers(prog) ;
    return ;
}

void Cone::Draw() {
    
    glFrontFace(GL_CCW) ;
    //glEnable(GL_CULL_FACE) ;
    glDisable(GL_CULL_FACE) ;
    
    glBindVertexArray(_vao);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0,_n*_n*6 );
    checkError() ;
    glBindVertexArray(0) ;
    
}

void GetVertexCone(VertexData &vd, float u, float v)
{
    float radius = 1.0 - v ;
    
    vd.position[0] = radius*cos(u*2*M_PI);
    vd.position[1] = radius*sin(u*2*M_PI) ;
    vd.position[2] = (v-0.5) ;
    vd.position[3] = 1.0 ;
    
    glm::vec3 n(cos(u*2*M_PI), sin(u*2*M_PI), 1.0) ;
    vd.normal = glm::normalize(n) ;
    
    vd.colour = vec4(1.0,0.0,0.0,1.0) ;
    
    vd.texCoord[0] = u ;
    vd.texCoord[1] = v ;
    
    return;
}

void Cone::SetBuffers(GLuint prog){ 
    
    if( _n < 1) return;
    
    VertexData *vertexDataArray = new VertexData[_n*_n*6] ;
    
    checkError() ;
    
    float du = 1.0 / (float) _n ;
    float dv = du ;
    // do it by quads made up of two triangles
    int count = 0 ;
    for( float u = 0 ; u < 1.0 ; u += du) {
        for( float v = 0 ; v < 1.0  ; v += dv) {
            //cerr << "----------------------------\n" ;
            //cerr << "(" << u << "," << v << ")" << endl ;
            //cerr << "(" << u+du << "," << v << ")" << endl ;
            //cerr << "(" << u+du << "," << v+dv << ")" << endl ;
            //cerr << "(" << u << "," << v+dv << ")" << endl ;
            
            // make them into triangles
            VertexData vd1,vd2,vd3,vd4 ;
            GetVertexCone(vd1, u,v) ;
            GetVertexCone(vd2, u+du,v) ;
            GetVertexCone(vd3, u+du,v+dv) ;
            GetVertexCone(vd4, u,v+dv) ;
            
            vertexDataArray[count++] = vd1 ;
            vertexDataArray[count++] = vd2 ;
            vertexDataArray[count++] = vd3 ;
            
            vertexDataArray[count++] = vd3 ;
            vertexDataArray[count++] = vd4 ;
            vertexDataArray[count++] = vd1 ;
            
            
            
        }
        
        
        GLuint colourAttribute, positionAttribute, normalAttribute, texCoordAttribute;
        getAttributeLocations(prog, positionAttribute, normalAttribute, colourAttribute, texCoordAttribute) ;
        
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);  checkError() ;
        // load the attribute data into the vbo
        glBufferData(GL_ARRAY_BUFFER, _n*_n*6*sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
        checkError() ;
        
        glEnableVertexAttribArray(positionAttribute);
        glEnableVertexAttribArray(colourAttribute);
        glEnableVertexAttribArray(normalAttribute) ;
        glEnableVertexAttribArray(texCoordAttribute) ;
        
        checkError() ;
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); // bind the vdo containing the attributes
        glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *)0);
        glVertexAttribPointer(colourAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) sizeof(vec4));
        glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4)));
        glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4) + sizeof(vec3)));
        
        checkError() ;
        glBindVertexArray(0) ;
        //cout << sizeof(VertexData) / (float) sizeof(GLfloat) << endl ;
        
    }
}

Sphere::Sphere(std::string name, int n, GLuint prog)
{
    if( n < 1) return ;
    _n = n ;
    SetBuffers(prog) ;
    return ;
}

void Sphere::Draw() {
    
    glFrontFace(GL_CW) ;
    //glEnable(GL_CULL_FACE) ;
    //glDisable(GL_CULL_FACE) ;
    
    glBindVertexArray(_vao);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0,_n*_n*6 );
    //checkError() ;
    glBindVertexArray(0) ;
    
}

void GetVertexSphere(VertexData &vd, float uu, float vv)
{
    //float v = 2*M_PI*vv - M_PI;
    //float u = 2*M_PI*uu  ;
    
    // epsilon
    //float e = 0.05; // in parametric space
    
    //float v = M_PI*(vv*(1-e) + e) ;
    float v = M_PI*vv ;
    float u = 2*M_PI* uu ;
    vd.position[0] = cos(u)*sin(v);
    vd.position[1] = sin(u)*sin(v) ;
    vd.position[2] = cos(v) ;
    vd.position[3] = 1.0 ;
    
    vd.normal[0] = vd.position[0] ;
    vd.normal[1] = vd.position[1] ;
    vd.normal[2] = vd.position[2] ;
    
    vd.colour = vec4(1.0,0.0,0.0,1.0) ;
    
    vd.texCoord[0] = uu ;
    vd.texCoord[1] = vv ;
    //std::cerr << vv << ", " << uu << std::endl ;
    
    return;
}

void Sphere::SetBuffers(GLuint prog){
    
    if( _n < 1) return;
    
    VertexData *vertexDataArray = new VertexData[_n*_n*6] ;
    
    checkError() ;
    
    float du = 1.0 / (float) _n ;
    float dv = du ;
    // do it by quads made up of two triangles
    int count = 0 ;
    for( float u = 0 ; u < 1.0 ; u += du) {
        for( float v = 0 ; v < 1.0  ; v += dv) {
            //cerr << "----------------------------\n" ;
            //cerr << "(" << u << "," << v << ")" << endl ;
            //cerr << "(" << u+du << "," << v << ")" << endl ;
            //cerr << "(" << u+du << "," << v+dv << ")" << endl ;
            //cerr << "(" << u << "," << v+dv << ")" << endl ;
            
            // make them into triangles
            VertexData vd1,vd2,vd3,vd4 ;
            GetVertexSphere(vd1, u,v) ;
            GetVertexSphere(vd2, u+du,v) ;
            GetVertexSphere(vd3, u+du,v+dv) ;
            GetVertexSphere(vd4, u,v+dv) ;
            
            if( !flip(vd1,vd2,vd3) ) {
                vertexDataArray[count++] = vd1 ;
                vertexDataArray[count++] = vd2 ;
                vertexDataArray[count++] = vd3 ;
            }
            else {
                vertexDataArray[count++] = vd1 ;
                vertexDataArray[count++] = vd3 ;
                vertexDataArray[count++] = vd2 ;
            }
            
            
            if( !flip(vd3,vd4,vd1) ) {
                vertexDataArray[count++] = vd3 ;
                vertexDataArray[count++] = vd4 ;
                vertexDataArray[count++] = vd1 ;
            }
            else {
                vertexDataArray[count++] = vd3 ;
                vertexDataArray[count++] = vd1 ;
                vertexDataArray[count++] = vd4 ;
            }
            
        }
        
        
        GLuint colourAttribute, positionAttribute, normalAttribute, texCoordAttribute;
        getAttributeLocations(prog, positionAttribute, normalAttribute, colourAttribute, texCoordAttribute) ;
        
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        checkError() ;
        // load the attribute data into the vbo
        glBufferData(GL_ARRAY_BUFFER, _n*_n*6*sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
        checkError() ;
        
        glEnableVertexAttribArray(positionAttribute);
        glEnableVertexAttribArray(colourAttribute);
        glEnableVertexAttribArray(normalAttribute) ;
        glEnableVertexAttribArray(texCoordAttribute) ;
        checkError() ;
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); // bind the vdo containing the attributes
        glVertexAttribPointer(positionAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *)0);
        glVertexAttribPointer(colourAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) sizeof(vec4));
        glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4)));
        glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid *) (2*sizeof(vec4) + sizeof(vec3)));
        
        checkError() ;
        glBindVertexArray(0) ;
        //cout << sizeof(VertexData) / (float) sizeof(GLfloat) << endl ;
        
    }
}
