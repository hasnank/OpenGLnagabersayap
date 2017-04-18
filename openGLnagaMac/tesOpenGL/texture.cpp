//
//  texture.cpp
//  tesOpenGL
//
//  Created by Dharma Kurnia Septialoka on 4/17/17.
//  Copyright © 2017 Dharma Kurnia Septialoka. All rights reserved.
//

#include "texture.hpp"
#include "stb_image.h"
#include <assert.h>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
    
    if (imageData == NULL) {
        std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
    }
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP for not repeating more pixels
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // minification fewer pixel, GL_LINEAR interpolate linearly within pixels
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // magnification
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    stbi_image_free(imageData);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit) {
    
    assert(unit >= 0 && unit <= 31);
    
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}