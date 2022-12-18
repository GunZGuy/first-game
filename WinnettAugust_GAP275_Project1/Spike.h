#pragma once
#include "GameObject.h"
#include "ColliderComponent.h"
#include <vector>

class Spike :
    public GameObject
{
private:
    SDL_Rect m_damage;

    SDL_Texture* m_pTexture;

    ColliderComponent m_collider;

public:
    Spike(SDL_Renderer* pRenderer, int x, int y, SDL_Rect transform, CollisionReferee* pReferee);
    ~Spike();

    virtual const char* GetName() override { return "damage"; }

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual bool doesDamage(ColliderComponent* pCollider) { return true; }
    virtual bool doesHeal(ColliderComponent* pCollider) { return false; }
};

