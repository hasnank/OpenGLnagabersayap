//
//  display.hpp
//  tesOpenGL
//
//  Created by Dharma Kurnia Septialoka on 4/10/17.
//  Copyright © 2017 Dharma Kurnia Septialoka. All rights reserved.
//

//#ifndef display_hpp
//#define display_hpp
//
//#include <stdio.h>
//
//#endif /* display_hpp */


#pragma once

#include <string>
#include <SDL2/SDL.h>
class Display
{
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();
    
    void Clear(float r, float g, float b, float a);
    void Update();
    bool IsClosed();
private:
    Display(const Display& other) {}
    void operator=(const Display& other) {}
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    
    bool m_isClosed;
};