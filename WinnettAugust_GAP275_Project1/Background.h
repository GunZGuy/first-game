#pragma once
#include "GameObject.h"
#include "ColliderComponent.h"

//Holds the information for creating a background
class Background :
    public GameObject
{
private:
    //A rect used for filling the screen
    SDL_Rect m_background[30][30];

    SDL_Texture* m_pBackground;
public:
    Background(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee);
    ~Background();

    void Render(SDL_Renderer* pRenderer);
};

