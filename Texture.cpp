#include"Texture.h"
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
SDL_Texture* loadText(string text_, string textFont, SDL_Color textColor_, int size,int& width, int& height, SDL_Renderer* renderer) {
    gFont = TTF_OpenFont(textFont.c_str(), size);
    if (gFont == NULL) {
        cout << "Could not load font ! " << endl;
    }

    SDL_Texture* newtexture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text_.c_str(), textColor_);
    if (textSurface == NULL) {
        cout << "Could not create text surface ! " << endl;
    }
    else {
        newtexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (newtexture == NULL) {
             cout << "Could not load texture ! " << endl;
        }
        else {
            width = textSurface->w;
            height = textSurface->h;
        }
    }
    return newtexture;
}
std::string HighScore_File(std::string path)
{
	std::fstream HighScoreFile;
	std::string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}
int ConvertToInt( string s)
{   
    int n = 0;
    for (int i = 0; i < s.length(); i++)
    {
        n = n * 10 + (s[i] - '0');
    }
    return n;
}
string UpdateHighScore(std::string path,
	 const int& score, 
	 std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	

	HighScoreFile.open(path, std::ios::out);

	 oldHighScore=ConvertToInt(old_high_score);
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
	return newHighScore;
}



