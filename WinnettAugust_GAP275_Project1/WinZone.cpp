#include "WinZone.h"
#include "SDL_image.h"
#include <iostream>

WinZone::WinZone(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee, ExampleGame* pGame)
    : m_collider(this, transform, pReferee)
    , m_winzone()
    , m_pTexture()
    , m_game(pGame)
{
    SDL_Surface* pImageSurface = IMG_Load("assets/winzone.png");
    if (pImageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    m_winzone.x = transform.x;
    m_winzone.y = transform.y;
    m_winzone.w = 50;
    m_winzone.h = 50;

    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
    if (m_pTexture == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(pImageSurface);
}

WinZone::~WinZone()
{
    SDL_DestroyTexture(m_pTexture);
}

void WinZone::Update(double deltaTime)
{
}

void WinZone::Render(SDL_Renderer* pRenderer)
{

    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(m_pTexture, 100);
    SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_winzone);
}

void WinZone::OnCollision(ColliderComponent* pOtherCollider)
{
    const char* getName = pOtherCollider->GetOwner()->GetName();
    if (getName == "player")
    {
        m_game->LoadScene(ExampleGame::GameWin);
    }
}
