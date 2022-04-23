#include<iostream>
#include"SDL.h"
#include"SDL_image.h"
#include "map.h"
using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;
const string WINDOW_TITLE = "VIET DUC COP CODE";

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();
void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
//ham khoi tao cac thuoc tinh ban dau
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP)
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
// xac dinh su kien ban phim
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
// Ham load cac image
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cout << "Unable to load image " << path << "SDL_image Error: " << IMG_GetError() << endl;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            cout << "Unable to create Texture from " << path << "SDL Error" << SDL_GetError() << endl;

        }


    }
    return newTexture;
}
void ApplyMap();
// ham de load cac image vao screen
void draw(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect  rect;
    rect.x = x;
    rect.y = y;
    rect.h = 10;
    rect.w = 10;

    SDL_SetRenderDrawColor(renderer, 0, 225, 0, 225);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
bool check(int x, int y, int maxx, int maxy) {
    if (x <= maxx && y <= maxy && x >= 0 && y >= 0)return true;
    return false;
}
//SDL_Texture* loadTexture(const char* name, SDL_Renderer* renderer) {
//    SDL_Surface* tempSur = IMG_Load(name);
//    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSur);

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
void ApplyMap();
bool check(int x, int y, int maxx, int maxy);
void draw(SDL_Renderer* renderer, int x, int y);
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);


    // Your drawing code here
    // Background and character's image
    SDL_Texture* background0 = loadTexture("imagetexture/Layer_0000_9.png", renderer);
    SDL_Texture* background1 = loadTexture("imagetexture/Layer_0001_8.png", renderer);
    SDL_Texture* background2 = loadTexture("imagetexture/Layer_0002_7.png", renderer);
    SDL_Texture* background3 = loadTexture("imagetexture/Layer_0003_6.png", renderer);
    SDL_Texture* background4 = loadTexture("imagetexture/Layer_0004_Lights.png", renderer);
    SDL_Texture* background5 = loadTexture("imagetexture/Layer_0005_5.png", renderer);
    SDL_Texture* background6 = loadTexture("imagetexture/Layer_0006_4.png", renderer);
    SDL_Texture* background7 = loadTexture("imagetexture/Layer_0007_Lights.png", renderer);
    SDL_Texture* background8 = loadTexture("imagetexture/Layer_0008_3.png", renderer);
    SDL_Texture* background9 = loadTexture("imagetexture/Layer_0009_2.png", renderer);
    SDL_Texture* background10 = loadTexture("imagetexture/Layer_0010_1.png", renderer);
    SDL_Texture* background11 = loadTexture("imagetexture/Layer_0011_0.png", renderer);


    //SDL_RenderPresent(renderer);
    SDL_Texture* girl = loadTexture("imagetexture/player2.png", renderer);
    SDL_Rect girlRect;
    SDL_QueryTexture(girl, NULL, NULL, &girlRect.w, &girlRect.h);
    girlRect.x = 100;
    girlRect.y = 562;
    girlRect.w = 100;
    girlRect.h = 100;

    //demoAnimation
    int x =  SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 2;
    int STEP = 5;
    SDL_Event e;
    bool gamerun = true;
    bool jump = false;
    double jumppxl = 10;

    while (gamerun) {

        while(SDL_PollEvent(&e))
        {
            SDL_Delay(10);
            if (e.type == SDL_QUIT){
                gamerun = false;
                break;
            }

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE: jump = true; break;// nhay
                    // case SDLK_UP: girlRect.y -= STEP; break;
                    //case SDLK_DOWN: girlRect.y += STEP; break;
                    case SDLK_LEFT: girlRect.x -= STEP; break;
                    case SDLK_RIGHT:girlRect.x += STEP; break;
                }
            }
        }
        // old jump

        if (jump)
        {   
            if (jumppxl >= -10)
            {
                girlRect.y -= int((jumppxl * abs(jumppxl)) * 0.3);
                // girlRect.x += 4; // nhay vong
                jumppxl--;
            }
            else {
                // girlRect.y = oldpos;
                jump = false;
                jumppxl = 10;
            }
        }
        SDL_RenderCopy(renderer, background8, 0, 0);
        // SDL_RenderCopy(renderer, background9, 0, 0);
        // SDL_RenderCopy(renderer, background11, 0, 0);
        SDL_RenderCopy(renderer, background10, 0, 0);
        SDL_RenderCopy(renderer, background0, 0, 0);
        SDL_RenderCopy(renderer, background1, 0, 0);
        SDL_RenderCopy(renderer, background2, 0, 0);
        // SDL_RenderCopy(renderer, background3, 0, 0);
        SDL_RenderCopy(renderer, background4, 0, 0);
        SDL_RenderCopy(renderer, background5, 0, 0);
        //SDL_RenderCopy(renderer, background6, 0, 0);
        SDL_RenderCopy(renderer, background3, 0, 0);
        SDL_RenderCopy(renderer, background7, 0, 0);
        // SDL_RenderCopy(renderer, background8, 0, 0);
        //SDL_RenderCopy(renderer, background9, 0, 0);
        // SDL_RenderCopy(renderer, background10, 0, 0);
        //SDL_RenderCopy(renderer, background11, 0, 0);



        SDL_RenderCopy(renderer, girl, NULL, &girlRect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }

    //load Screen Waiting;
    //Choose the character;

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
