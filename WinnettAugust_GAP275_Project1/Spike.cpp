#include "Spike.h"
#include "SDL_image.h"
#include <iostream>

Spike::Spike(SDL_Renderer* pRenderer, int x, int y, SDL_Rect transform, CollisionReferee* pReferee)
    : m_collider(this, transform, pReferee)
    , m_pTexture(nullptr)
    , m_damage()
{
    //Create Surface, error checking, and setting x,y,w, and h
    SDL_Surface* pImageSurface = IMG_Load("assets/spike.png");
    if (pImageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    m_damage.x = transform.x;
    m_damage.y = transform.y;
    m_damage.w = 50;
    m_damage.h = 30;

    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
    if (m_pTexture == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(pImageSurface);
}

Spike::~Spike()
{
    SDL_DestroyTexture(m_pTexture);
}

void Spike::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_damage);
}
