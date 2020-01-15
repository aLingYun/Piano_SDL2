#ifndef PIANO_KEY_H
#define PIANO_KEY_H

#include <SDL2/SDL.h>

enum KEYCOLOR
{
    black,
    white
};

class PIANOKEY
{
private:
    SDL_Rect key;

public:
    PIANOKEY();
    PIANOKEY(SDL_Rect kk);
    ~PIANOKEY();

    void showKey(SDL_Renderer* rend, KEYCOLOR key_color);
    void setKey(SDL_Rect kk);
    SDL_Rect getKey();
};

#endif