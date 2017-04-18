//
//  shader.hpp
//  tesOpenGL
//
//  Created by Dharma Kurnia Septialoka on 4/10/17.
//  Copyright © 2017 Dharma Kurnia Septialoka. All rights reserved.
//

//#ifndef shader_hpp
//#define shader_hpp
//
//#include <stdio.h>
//
//#endif /* shader_hpp */

#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
    Shader(const std::string& fileName);
    
    void Bind();
    
    virtual ~Shader();
private:
    static const unsigned int NUM_SHADERS = 2;
    
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};

