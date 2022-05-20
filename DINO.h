#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "BaseObject.h"
#define SPEED 10

class Dino 
{
    public:
        Dino(int _x, int _y,SDL_Renderer* renderer);
        void animationconfig();
        void Display();
        void Jump();
        bool Jumpable(){return jump;}
        void User_input(SDL_Event& e, Mix_Chunk* jump_s = NULL);
        SDL_Rect GetRect(int x, int y);
    
        int x,y;
        int width,height;
        double jumppxl;
        bool jump;
        
        SDL_Renderer* screen;
        SDL_Rect frame_clip[6];
        int frame; 
        SDL_Texture* tex;
};