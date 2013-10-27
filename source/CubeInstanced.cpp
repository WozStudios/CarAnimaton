#include "CubeInstanced.h"

CubeInstanced::CubeInstanced(std::string name, GLuint prog)
{
    SetBuffers(prog) ;
    return ;
}

void CubeInstanced::SetBuffers(GLuint prog)
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

void CubeInstanced::Draw(void)
{
    glFrontFace(GL_CCW) ;
    glCullFace(GL_BACK);
    
    glEnable(GL_CULL_FACE) ;
    //glDisable(GL_CULL_FACE) ;
    
    glBindVertexArray(_vao);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0) ;
}