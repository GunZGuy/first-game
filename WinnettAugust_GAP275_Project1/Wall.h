#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "ColliderComponent.h"

class Wall :
    public GameObject
{
private:
    static const int numOfTextures = 5;
    SDL_Rect m_Wall[numOfTextures];

    ColliderComponent m_collider;

    SDL_Texture* m_pTexture;

    double m_x;
public:
    Wall(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee);
    ~Wall();

    virtual const char* GetName() override { return "Wall"; }

    // Inherited via GameObject
    virtual void Update(double deltaTime) override;
    virtual void Render(SDL_Renderer* pRenderer) override;

    void OnCollision(ColliderComponent* pOtherCollider);

    virtual bool doesDamage(ColliderComponent* pCollider) { return false; }
    virtual bool doesHeal(ColliderComponent* pCollider) { return false; }
};

