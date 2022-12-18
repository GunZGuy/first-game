#include "Healing.h"
#include "SDL_image.h"
#include <iostream>

Healing::Healing(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee)
    : m_collider(this, transform, pReferee)
    , m_pTexture(nullptr)
    , m_healing()
    , m_fountain("assets/fountain.png", 12, 96, 96, 4, pRenderer)
{
    m_fountain.m_transform.x = transform.x;
    m_fountain.m_transform.y = transform.y;
    m_fountain.AddAnimationSequence("running", 0, 4);
    m_fountain.PlayAnimation("running");
}

Healing::~Healing()
{
}

void Healing::Update(double deltaTime)
{
    m_fountain.Update(deltaTime);
}

void Healing::Render(SDL_Renderer* pRenderer)
{
    m_fountain.Render(pRenderer);
}

void Healing::OnCollision(ColliderComponent* pOtherCollider)
{
}

