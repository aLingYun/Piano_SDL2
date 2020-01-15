#include "piano_key.h"

PIANOKEY::PIANOKEY()
{
}

PIANOKEY::PIANOKEY(SDL_Rect kk):key(kk)
{
}

PIANOKEY::~PIANOKEY()
{
}

void PIANOKEY::showKey(SDL_Renderer* rend, KEYCOLOR key_color)
{
    if(key_color == white)
    {
        SDL_SetRenderDrawColor(rend, 255,255,255,0);
    }
    else
    {
        SDL_SetRenderDrawColor(rend, 0,0,0,0);
    }
    SDL_RenderFillRect(rend, &key);
    SDL_SetRenderDrawColor(rend, 0,0,0,0);
    SDL_RenderDrawRect(rend, &key);
}

void PIANOKEY::setKey(SDL_Rect kk)
{
    key = kk;
}

SDL_Rect PIANOKEY::getKey()
{
    return key;
}