#pragma once
#include <SDL.h>
#include <string>
#include "Vector2.h"


class ColliderComponent;
class GameObject
{
public:
    virtual ~GameObject() {};

    virtual const char* GetName() { return "unnamed"; }

    virtual bool isWall(ColliderComponent* pCollider) { return true; }

    virtual bool isNotWall(ColliderComponent* pCollider) { return false; }

    virtual bool doesHeal(ColliderComponent* pCollider) { return true; }

    virtual bool doesDamage(ColliderComponent* pCollider) { return true; }

    virtual void Update(double deltaTime) { }

    virtual void Render(SDL_Renderer* pRenderer) { }

    virtual void OnCollision(ColliderComponent* pCollider) {  }

    virtual void HandleEvent(SDL_Event* pEvent) { }

    virtual bool Move(Vector2<float> direction, float speedMultiplier = 1) { return true; }

    virtual Vector2<float> GetPosition() { return Vector2<float>{0, 0}; }
};

