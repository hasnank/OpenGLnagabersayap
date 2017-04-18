//
//  texture.hpp
//  tesOpenGL
//
//  Created by Dharma Kurnia Septialoka on 4/17/17.
//  Copyright © 2017 Dharma Kurnia Septialoka. All rights reserved.
//

#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
    Texture(const std::string& fileName);
    
    void Bind(unsigned int unit);
    
    virtual ~Texture();
protected:
private:
    
    GLuint m_texture;
};


