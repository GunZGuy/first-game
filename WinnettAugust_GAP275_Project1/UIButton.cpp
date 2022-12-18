#include "UIButton.h"
#include "SDL_image.h"
#include <iostream>

UIButton::UIButton(SDL_Rect transform, SDL_Renderer* pRenderer, const char* filePath
    , const char* filePathHighlighted)
    : m_transform(transform)
    , m_pHighlightTexture()
    , m_isHighlighted(false)
    , m_pTexture(nullptr)
{
    SDL_Surface* pImageSurface = IMG_Load(filePath);
    if (pImageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
    if (m_pTexture == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(pImageSurface);

    SDL_Surface* pImageSurface2 = IMG_Load(filePathHighlighted);
    if (pImageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    m_pHighlightTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface2);
    if (m_pTexture == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(pImageSurface2);
}

UIButton::~UIButton()
{
    SDL_DestroyTexture(m_pTexture);
    SDL_DestroyTexture(m_pHighlightTexture);
}

void UIButton::Trigger()
{
    if (m_callback != nullptr)
    {
        m_callback();
    }
}

void UIButton::Render(SDL_Renderer* pRenderer)
{
    SDL_Texture* clr = m_isHighlighted ? m_pHighlightTexture : m_pTexture;
    SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
    SDL_RenderCopy(pRenderer, clr, nullptr, &m_transform);

}

void UIButton::HandleEvent(SDL_Event* pEvent)
{
    switch (pEvent->type)
    {
    case SDL_MOUSEMOTION:
        m_isHighlighted = HitTest(pEvent->button.x, pEvent->button.y);
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (m_callback != nullptr && HitTest(pEvent->button.x, pEvent->button.y))
        {
            Trigger();
        }
        break;
    }
}

bool UIButton::HitTest(int x, int y)
{
    return (x >= m_transform.x && x <= m_transform.x + m_transform.w &&
             y >= m_transform.y && y <= m_transform.y + m_transform.h);
}
