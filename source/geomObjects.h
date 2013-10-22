//
//  geomObjects.h
//  cse3431Template
//
//  Created by Petros Faloutsos on 9/23/12.
//  Copyright (c) 2012 Petros Faloutsos. All rights reserved.
//

#ifndef cse3431Template_geomObjects_h
#define cse3431Template_geomObjects_h


class Object {
public:
    Object() {_name = "" ;} ;
    Object(std::string name) { _name = name ;} ;
    virtual void Draw(void) {return;}  ;
    std::string GetName() { return _name;} ;
    void getAttributeLocations(GLuint prog, GLuint &pa,
                               GLuint &na, GLuint &ca,
                               GLuint &ta);
    void binVAO(void) { glBindVertexArray(_vao) ;} ;
    
protected:
    std::string _name ;
    GLuint  _vbo ;
    GLuint _vao ;
   
};

class Square : public Object {
public:
    Square() { return ;} ;
    Square(std::string name, GLuint prog) ;
    void Draw(void) ;
    void SetBuffers(GLuint prog) ;
} ;

class Cube : public Object {
public:
    Cube() { return ;} ;
    Cube(std::string name, GLuint prog) ;
    void Draw(void) ;
    void SetBuffers(GLuint prog) ;
} ;

class Cylinder : public Object {
public:
    Cylinder() { _n = 0 ;return ;};
    Cylinder(std::string name, int nSub, GLuint prog) ;
    void Draw(void) ;
    void SetBuffers(GLuint prog) ;
    int getN(void) {return _n;} ;
private:
    int _n ; // number of subdivision in each paramater
};

class Cone : public Object {
public:
    Cone() { _n = 0 ;return ;};
    Cone(std::string name, int nSub, GLuint prog) ;
    void Draw(void) ;
    void SetBuffers(GLuint prog) ;
    int getN(void) {return _n;} ;
private:
    int _n ; // number of subdivision in each paramater
};


class Sphere : public Object {
public:
    Sphere() { _n = 0 ; return ;}
    Sphere(std::string name, int nSub, GLuint prog);
    void Draw(void) ;
    void SetBuffers(GLuint prog) ;
    int getN(void) {return _n;} ;
private:
    int _n ; // number of subdivision in each paramater
};
    

#endif
