#include<iostream>
#include"DINO.cpp"
#include"BaseObject.h"
#include "Enemy.cpp"
#include"Collision.cpp"
#include"Texture.cpp"

SDL_Renderer* gRenderer = nullptr;
Mix_Chunk* jump_s = NULL;
Mix_Chunk* glose = NULL;
Mix_Music* g_menu = NULL;
int flag = 0;
Uint8 a = 255;

int width_name = 0, height_name = 0;
int width_play = 0, height_play = 0;
int width_exit = 0, height_exit = 0;

bool checkClick = false;
bool checkExit = false;

using namespace std;
const string WINDOW_TITLE = "VIET DUC TAP LAM CODER";
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

    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize ! " << endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer could not initialize ! " << endl;
    }
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
    }
}
void handleClick (SDL_Event& e, int posX, int posY, int& width_, int& height_, bool& checkClick , Mix_Chunk* click_s) {
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		int pos_X_ = posX, pos_Y_ = posY;
		bool inside = true;

		if (x < posX) {
			inside = false;
		}
		else if (x > posX + width_) {
			inside = false;
		}
		else if (y < posY) {
			inside = false;
		}
		else if (y > posY + height_) {
			inside = false;
		}

		if (!inside) {
			posX = pos_X_;
			posY = pos_Y_;
		}
		else {
			switch (e.type) {
			case SDL_MOUSEMOTION:
				posX = pos_X_;
				posY = pos_Y_;
				break;
			case SDL_MOUSEBUTTONDOWN:
				posX -= 3;
				posY += 3;
               //sua 
               if(Mix_PlayingMusic()==1){ Mix_PauseMusic();}
				checkClick = true;
				break;
			case SDL_MOUSEBUTTONUP:
				posX = pos_X_;
				posY = pos_Y_;
				break;
			}
		}
	}
}
int main(int argc, char* argv[])
{   
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    
    jump_s = Mix_LoadWAV("Sound/Dino_jump_sound.wav");
    glose = Mix_LoadWAV("Sound/Dino_Lose.wav");
    g_menu = Mix_LoadMUS("Sound/Menu_Sound.mp3");


				int score = 0;
				int acceleration = 0;
              
				std::string highscore =HighScore_File("HighScore/HighScore.txt");
				
				Enemy enemy1(ON_GROUND_ENEMY);
				Enemy enemy2(ON_GROUND_ENEMY);
				Enemy enemy3(IN_AIR_ENEMY);


    // --------------------MENU---------------------
    SDL_Color textColor = {255, 255, 131};
    SDL_Color textColor1 = {134, 255, 255};
    SDL_Texture* menuBackGround = loadTexture("imagetexture/MenuBackGround_.png", renderer);
    SDL_Rect menuBackGround_ = {0, 0, 860, 520};

    SDL_SetTextureBlendMode(menuBackGround, SDL_BLENDMODE_BLEND);
    SDL_Texture* Game_Name = loadText("DINO IN JUNGLE", "Dino_Font/Font.ttf", textColor, 100, width_name, height_name, renderer);
    SDL_Rect Game_Name_ = {100, 100, width_name, height_name};

    SDL_Texture* PlayText = loadText("PLAY", "Dino_Font/Font.ttf", textColor1, 70, width_play, height_play, renderer);
    SDL_Rect PlayText_ = {350, 250, width_play, height_play};

    SDL_Texture* ExitText = loadText("EXIT", "Dino_Font/Font.ttf", textColor1, 70, width_exit, height_exit, renderer);
    SDL_Rect ExitText_ = {350, 350, width_exit, height_exit};

    // Background and character's image
    SDL_Texture* background = loadTexture("imagetexture/backgr.png", renderer);
    SDL_Rect background1={0,0,1280,520};
    SDL_Rect background2;
    background2.h=520;
    background2.w=1280;
    background2.y=0;
    //Dinosaur
    Dino duc(60,358,renderer);
    duc.animationconfig();
    //SDL_RenderPresent(renderer);
    SDL_Texture* bat = loadTexture("imagetexture/enemy1.png",renderer);
    SDL_Rect BatRect={0,0,43,30};
    SDL_Rect spbat={0,0,45,30};

    SDL_Texture* catus= loadTexture("imagetexture/enemy2.png",renderer);
    SDL_Rect catus1={0,GROUND+12,65,75};
    SDL_Rect catus2={0,GROUND+19,50,65};
    int STEP = 5;    
    SDL_Event e;
    bool gamerun = true;
    SDLCommonFunc character;

    int check = 0;
    SDL_Texture* game_over = loadTexture("imagetexture/over_.png", renderer);
    // 860 520  600  259 
    SDL_Rect game_over_ = {-170, 200, 1200, 260};

    bool check_space = false;

    while (gamerun) {

        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                gamerun = false;
                break;
            }else{
                duc.User_input(e, jump_s);
                if (flag == 0) {
                    handleClick(e, 350, 250, width_play, height_play, checkClick, NULL);
                    handleClick(e, 350, 350, width_exit, height_exit, checkExit, NULL);
                }
                if (check_space) {
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                        score = 0;
                        background1.x = 0;
                        background2.x = 0;
                        duc.y = 358;
                        check_space = false;
                        enemy1.setposX();
                        enemy2.setposX();
                        enemy3.setposX();
                    }
                }
            }
        }

        if (checkExit) exit(0);

        if (checkClick) {

        if (flag == 0) {
            while (a > 0) {
                a -= 5;
                
                SDL_RenderCopy(renderer, background, 0, &background1);
                SDL_SetTextureAlphaMod(menuBackGround, a);
                SDL_RenderCopy(renderer, menuBackGround, 0, &menuBackGround_);
                SDL_RenderPresent(renderer);                
            }
            flag++;
            a = 255;
        }
        if (!check_space) {
        background1.x+=-10;
        background2.x=background1.x+background1.w;
        }
        //score 
        int score_height=0; int score_width=0;
         if (!check_space) score+=1;
         string _score=to_string(score);
         string s = "Score:";
          s+=_score;
        SDL_Texture* gscore=loadText(s, "Dino_Font/Font.ttf",textColor,30,score_width,score_height,renderer);
        SDL_Rect gcore_={470,20,score_width,score_height};
        //highscore
          string hscore="HighScore:";
          int hscore_height=0; int hscrore_width=0;
        string   HighScore_File(highscore);
          hscore+=UpdateHighScore("HighScore/HighScore.txt",score,highscore);
          SDL_Texture* gHighScore=loadText(hscore,"Dino_Font/Font.ttf",textColor,30,hscrore_width,hscore_height,renderer);
          SDL_Rect gHighScore_={650,20,hscrore_width,hscore_height};
        // old jump
        if(duc.Jumpable())
        {   
            duc.Jump();
        }
        if(background2.x<=0){
            background1.x=0;
        }
        SDL_RenderCopy(renderer, background, 0, &background1);
        SDL_RenderCopy(renderer,background, 0 , &background2);
        SDL_RenderCopy(renderer,gscore,0,&gcore_);
        SDL_RenderCopy(renderer,gHighScore,0,&gHighScore_);

        if (!check_space) {
        enemy1.Move(acceleration);
        catus1.x=enemy1.GetPosX();
        SDL_RenderCopy(renderer,catus,0,&catus1);
        
        enemy2.Move(acceleration);
        catus2.x=enemy2.GetPosX();
        SDL_RenderCopy(renderer,catus,0,&catus2);

        enemy3.Move(acceleration);
        spbat.x = enemy3.GetPosX();
        spbat.y = enemy3.GetPosY();
        
        if(BatRect.x<162){
            BatRect.x +=43;
        }
        else BatRect.x = 0;
        SDL_RenderCopy(renderer, bat, &BatRect , &spbat);
        }
        SDL_Rect rex = duc.GetRect(duc.x, duc.y);
        if (!check_space) {
            if (character.CheckCollision(rex, spbat) == true || character.CheckCollision(rex, catus1) == true || character.CheckCollision(rex, catus2) == true) 
            {   
                Mix_PlayChannel(-1,glose,0);
                check_space = true;
                duc.y = 600;
            } 
        }
         if (check_space) {
                SDL_RenderCopy(renderer, game_over, 0, &game_over_);}
            
        duc.Display();
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
        else {
             if(Mix_PlayingMusic()!=1){Mix_PlayMusic(g_menu,-1);}
             SDL_RenderCopy(renderer, menuBackGround, 0, &menuBackGround_);
             SDL_RenderCopy(renderer, Game_Name, 0, &Game_Name_);
             SDL_RenderCopy(renderer, PlayText, 0, &PlayText_);
             SDL_RenderCopy(renderer, ExitText, 0, &ExitText_);

             SDL_RenderPresent(renderer);  
        }
    }

    //load Screen Waiting;
    //Choose the character;
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}