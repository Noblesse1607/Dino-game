#include"DINO.h"
#include"BaseObject.h"
using namespace std;

Dino::Dino(int _x,int _y,SDL_Renderer* renderer):x(_x),y(_y),screen(renderer)
{
    jump = false;
    tex = IMG_LoadTexture(screen,"imagetexture/Saur.png");
    
    width = 57;
    height = 57;
    jumppxl = 9; 
    frame = 0;
}

void Dino::animationconfig()
{
    if(width > 0 && height > 0)
    {
        for(int i = 0; i < 6;i++)
        {
            frame_clip[i].x =  i*width;
            frame_clip[i].y =  0;
            frame_clip[i].w =  width;
            frame_clip[i].h =  height;
        }
    }
}


void Dino::Display()
{   
    frame++;
    if(frame >= 24 )
    {
        frame = 0;
    }
    
    SDL_Rect showclip = {x,y,100,100};
    SDL_Rect* frame_clip_dino = &frame_clip[frame/4];
    SDL_RenderCopy(screen,tex,frame_clip_dino,&showclip);
}

void Dino::Jump()
{
    if (jumppxl >= -9)
    {
        y -= int((jumppxl * abs(jumppxl)) * 0.3);
        jumppxl-=0.5;
    }
    else {
        jump = false;
        jumppxl = 9;
    }
}

void Dino::User_input(SDL_Event& e, Mix_Chunk* jump_s)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym) {
            case SDLK_SPACE:
            {   
                Mix_PlayChannel(-1, jump_s, 0);
                jump = true;
            }
            break;// nhay
            // case SDLK_UP: girlRect.y -= STEP; break;
            //case SDLK_DOWN: girlRect.y += STEP; break;
        }
    }
    
}

SDL_Rect Dino::GetRect(int x, int y) {
    SDL_Rect rex = {rex.x = x, rex.y = y, rex.h = 57, rex.w = 57};
    return rex;
}
