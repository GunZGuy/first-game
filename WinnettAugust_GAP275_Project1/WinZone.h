#pragma once
#include "GameObject.h"
#include "CollisionReferee.h"
#include "StateWinGame.h"
#include "ExampleGame.h"
#include "ExampleGameplay.h"
#include "RNG.h"

class ExampleGameplay;
class RNG;

class WinZone :
    public GameObject
{
private:

    SDL_Rect m_winzone;

    SDL_Texture* m_pTexture;

    ColliderComponent m_collider;

    ExampleGame* m_game;

public:
    RNG* random;

    WinZone(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee, ExampleGame* pGame);
    ~WinZone();

    void Update(double deltaTime);

    virtual const char* GetName() override { return "Win Zone"; }

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual bool isWall(ColliderComponent* pCollider) { return false; }

    virtual bool doesHeal(ColliderComponent* pCollider) { return false; }

    virtual bool doesDamage(ColliderComponent* pCollider) { return false; }

    void OnCollision(ColliderComponent* pOtherCollider);

};

