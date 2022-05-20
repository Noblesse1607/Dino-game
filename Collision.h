#pragma once

#include"BaseObject.h"
#include "Enemy.h"
class SDLCommonFunc
{
public:
    bool CheckCollision(const SDL_Rect& object, const SDL_Rect& other_object);
};

