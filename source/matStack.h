#ifndef _MatStack_
#define _MatStack_

#include "glm/glm.hpp"
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Debug.h"

// NOT THE MOST EFFICIENT IMPLEMENTATION




class ModelviewStack {
    
private:
    int _MAX;
    int _top;
    glm::mat4* _items;
    glm::mat4 _viewMat ;
    
public:
    ModelviewStack(int size){
        _MAX = size;
        _top = -1;
        _items = new glm::mat4[_MAX];
    }
    
    ~ModelviewStack(){ delete [] _items; }
    
    void LoadIdentity(void) {
        _top = -1 ;
        Push(glm::mat4(1.0));
    }
    void Load(const glm::mat4 & m) {
        _top = -1 ;
        Push(m);
    }
    void Push(const glm::mat4 & m){
        if(Full()){
            std::cout << "Stack Full!" << std::endl;
            return ;
        }
        
        _items[++_top] = m;
    }
    
    const glm::mat4 Top() {
        if(Empty()){
            std::cout << "Stack Empty!" << std::endl;
            return( glm::mat4(1.0));
        }
        
        return(_viewMat*_items[_top]) ;
    }
    const glm::mat4 View() {
        return _viewMat ;
    }
    
    int Empty(){ return _top == -1; }
    
    int Full(){ return _top+1 == _MAX; }
    
    void Rotate(float angle, const glm::vec3 & axis)
    {
        if( _top < 0) return ;
        _items[_top] = glm::rotate(_items[_top], angle, axis) ;
    }
    void Translate(const glm::vec3 & offset)
    {
        if( _top < 0) return ;
        _items[_top] = glm::translate(_items[_top], offset) ;
    }
    void Scale(const glm::vec3 & factors)
    {
        if( _top < 0) return ;
        _items[_top] = glm::scale(_items[_top], factors) ;
    }
    void SetViewMatrix(const glm::mat4 &m)
    {
        _viewMat = m ;
    }
    void SetViewMatrix(const glm::vec3 eye, const glm::vec3 ref, const glm::vec3 up)
    {
        _viewMat = glm::lookAt(eye,ref,up) ;
    }
    
    void Mult(const glm::mat4 &m)
    {
        if( _top < 0) return ;
        _items[_top] = _items[_top]*m;
    }
    void Push(void) {
        if(Full()){
            std::cout << "Stack Full!" << std::endl;
            return ;
        }
        
        _items[_top+1] = _items[_top];
        _top = _top + 1 ;
    }
    void Pop(void){
        if(Empty()){
            std::cout << "Stack Empty!" << std::endl;
            return ;
        }
        
        _top = _top - 1 ;
    }
};

#endif

