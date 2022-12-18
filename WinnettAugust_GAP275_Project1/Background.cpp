#include "Background.h"
#include "SDL_image.h"
#include <iostream>

Background::Background(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee)
    : m_background()
    , m_pBackground()
{
    //Set background image
    SDL_Surface* pImageSurface = IMG_Load("assets/grass.png");

    if (pImageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    m_pBackground = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);

    if (m_pBackground == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    //Fill rect with background image (tiled)
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            m_background[i][j].x = i * 128;
            m_background[i][j].y = j * 128;
            m_background[i][j].h = 128;
            m_background[i][j].w = 128;
        }
    }
    SDL_FreeSurface(pImageSurface);
}

Background::~Background()
{
    SDL_DestroyTexture(m_pBackground);
}

void Background::Render(SDL_Renderer* pRenderer)
{
    //Render full rect that was filled
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            SDL_RenderCopy(pRenderer, m_pBackground, nullptr, &m_background[i][j]);
        }
    }
}
