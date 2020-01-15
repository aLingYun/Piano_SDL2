#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "piano_key.h"

#define MACHINETYPE     COMPUTER  //ADROID

#define WHITEKEYNUM     22
#define BLACKKEYNUM     15
#define PIANOW          216
#define PIANOH          468
#define DISPLAYH        50
#define WHITEKEYW       (PIANOW - DISPLAYH)
#define WHITEKEYH       (PIANOH / WHITEKEYNUM)
#define BLACKKEYW       (WHITEKEYW*2/3)
#define BLACKKEYH       (WHITEKEYH*2/3)

char* blackWav[BLACKKEYNUM] = { "./res/a#.wav",
                                "./res/a.wav",
                                "./res/a1#.wav",
                                "./res/a1.wav",
                                "./res/A2#.wav",
                                "./res/A2.wav",
                                "./res/a3#.wav",
                                "./res/a3.wav",
                                "./res/a4#.wav",
                                "./res/a4.wav",
                                "./res/b.wav",
                                "./res/b1.wav",
                                "./res/B2.wav",
                                "./res/b3.wav",
                                "./res/b4.wav"
                                };
char* whiteWav[WHITEKEYNUM] = { "./res/c#.wav",
                                "./res/c.wav",
                                "./res/c1#.wav",
                                "./res/c1.wav",
                                "./res/c2#.wav",
                                "./res/c2.wav",
                                "./res/c3#.wav",
                                "./res/c3.wav",
                                "./res/c4#.wav",
                                "./res/c4.wav",
                                "./res/c5.wav",
                                "./res/d#.wav",
                                "./res/d.wav",
                                "./res/d1#.wav",
                                "./res/d1.wav",
                                "./res/d2#.wav",
                                "./res/d2.wav",
                                "./res/d3#.wav",
                                "./res/d3.wav",
                                "./res/d4#.wav",
                                "./res/d4.wav",
                                "./res/e.wav"
                                };

bool boPointInRect(SDL_Point point, SDL_Rect rect)
{
    if((point.x >= rect.x) && (point.x <= rect.x + rect.w) && (point.y >= rect.y) && (point.y <= rect.y + rect.h))
        return true;
    return false;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
    SDL_Window *window=SDL_CreateWindow("demo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,PIANOW,PIANOH,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    bool quit=false;
    SDL_Event event;
    SDL_Point point;
    Mix_Music *scratch = NULL;
    PIANOKEY keyWhite[WHITEKEYNUM];
    PIANOKEY keyBlack[BLACKKEYNUM];

    //scratch = Mix_LoadMUS(whiteWav[1]);

    for(int i=0; i<WHITEKEYNUM; i++)
    {
        keyWhite[i].setKey({0,i*WHITEKEYH,WHITEKEYW,WHITEKEYH});
        keyWhite[i].showKey(renderer,white);
    }
    for(int i=0,j=0; (i<WHITEKEYNUM) && (j<BLACKKEYNUM); i++)
    {
        if((i==2)||(i==6)||(i==9)||(i==13)||(i==16)||(i==20))
        {
            continue;
        }
        else
        {
            keyBlack[j].setKey({WHITEKEYW-BLACKKEYW,i*WHITEKEYH+WHITEKEYH-BLACKKEYH/2,BLACKKEYW,BLACKKEYH});
            keyBlack[j].showKey(renderer,black);
            j++;
        }
    }

    while(!quit){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit=true;
                    break;
#if MACHINETYPE == COMPUTER
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        point.x = event.button.x;
                        point.y = event.button.y;
                    }
                    break;
#elif MACHINETYPE == ANDROID
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_FINGERDOWN)
                    {
                        point.x = event.button.x;
                        point.y = event.button.y;
                    }
                    break;
#endif
                default:
                    break;
            }
        }
        for(int i=0;i<WHITEKEYNUM;i++)
        {
            SDL_Rect WhiteRectTemp = keyWhite[i].getKey();
            SDL_Rect BlackRectTemp = keyBlack[i].getKey();
            if(i<BLACKKEYNUM)
            {
                if(boPointInRect(point,BlackRectTemp))
                {
                    Mix_HaltMusic();
                    scratch = Mix_LoadMUS(blackWav[i]);
                    Mix_PlayMusic(scratch,1);
                    break;
                }
                if(boPointInRect(point,WhiteRectTemp))
                {
                    Mix_HaltMusic();
                    scratch = Mix_LoadMUS(whiteWav[i]);
                    Mix_PlayMusic(scratch,1);
                    break;
                }
            }
            else
            {
                if(boPointInRect(point,WhiteRectTemp))
                {
                    Mix_HaltMusic();
                    scratch = Mix_LoadMUS(whiteWav[i]);
                    Mix_PlayMusic(scratch,1);
                    break;
                }
            }
        }
        point = {PIANOW,PIANOH};
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    Mix_FreeMusic(scratch);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
