#ifndef ENEMY_H_
#define ENEMY_H_
#include"BaseObject.h"
#define ENEMY_MAX_HEIGHT 300
#define ENEMY_MIN_HEIGHT 330
#define ENEMY_POSITION_RANGE 350

class Enemy
{
public:
	Enemy(int _type = 0);
	
	~Enemy();

	void Move(const int& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	void setposX();

	int GetType();

	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();

	
private:
	int posX, posY;

	int eWidth, eHeight;

	int type;

	SDL_Texture *EnemyTexture;
};

#endif // !ENEMY_H_