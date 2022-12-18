#include "Wall.h"
#include "SDL_image.h"
#include <iostream>
#include <Windows.h>
#define SCREEN_W 800
#define SCREEN_H 600

Wall::Wall(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee)
    : m_pTexture(nullptr)
    , m_Wall()
    , m_x()
    , m_collider(this, transform, pReferee)
{
   // WIP -- NEED CLEANER SOLUTION -- LESS OBJECTS

    SDL_Surface* pImageSurface = IMG_Load("assets/stone2_b.jpg");
    if (pImageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    m_Wall[0].x = transform.x;
    m_Wall[0].y = transform.y;
    m_Wall[0].w = 50;
    m_Wall[0].h = 50;

    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
    if (m_pTexture == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(pImageSurface);

}

Wall::~Wall()
{
    SDL_DestroyTexture(m_pTexture);
}



void Wall::Update(double deltaTime)
{
}

void Wall::Render(SDL_Renderer* pRenderer)
{
    for (int i = 0; i < numOfTextures; ++i)
    {
        SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_Wall[i]);
    }
}

void Wall::OnCollision(ColliderComponent* pOtherCollider)
{
}
