#ifndef BASE_OBJECT_
#define BASE_OBJECT_

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>


#define TIME_MAX 1000
#define GROUND 358
#define MAX_HEIGHT 300

#define SPEED_INCREASEMENT 5
#define SCORE_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define ENEMY_SPEED 5
#define FLY_SPEED 8
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

using namespace std;
const int SCREEN_WIDTH = 860;
const int SCREEN_HEIGHT = 520;
const int SCREEN_BPP = 32;


#endif

