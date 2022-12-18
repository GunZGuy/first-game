#include "StaticImage.h"
#include <SDL_image.h>
#include <iostream>

StaticImage::StaticImage(SDL_Rect transform, const char* pImagePath, SDL_Renderer* pRenderer)
    : m_transform(transform)
    , m_pTexture(nullptr)
{
    SDL_Surface* pImageSurface = IMG_Load(pImagePath);

    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);

    SDL_FreeSurface(pImageSurface);
}

StaticImage::~StaticImage()
{
    SDL_DestroyTexture(m_pTexture);
}

void StaticImage::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}
