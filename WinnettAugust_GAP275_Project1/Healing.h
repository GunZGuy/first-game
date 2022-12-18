#pragma once
#include "GameObject.h"
#include "ColliderComponent.h"
#include <vector>
#include "AnimationComponent.h"
class Healing :
    public GameObject
{
    SDL_Rect m_healing;

    SDL_Texture* m_pTexture;

    ColliderComponent m_collider;

    AnimationComponent m_fountain;
public:
    Healing(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee);
    ~Healing();

    void Update(double deltaTime);

    virtual const char* GetName() override { return "healing"; }

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual bool isWall(ColliderComponent* pCollider) { return false; }

    virtual bool doesHeal(ColliderComponent* pCollider) { return true; }

    virtual bool doesDamage(ColliderComponent* pCollider) { return false; }

    void OnCollision(ColliderComponent* pOtherCollider);
};

