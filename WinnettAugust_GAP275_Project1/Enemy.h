#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "ColliderComponent.h"

class CollisionReferee;

class Enemy :
    public GameObject
{
protected:
    using Vector2 = Vector2<float>;

    const float m_kDetectDistanceSqr;

    GameObject* m_pTarget;

    AnimationComponent m_enemy;
    Vector2 m_position;
    Vector2 m_size;
private:


    ColliderComponent m_collider;

    const float m_kSpeed;

public:

    Enemy(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee,
        float speed = 30, float detectionRadius = 100);
    ~Enemy();


    virtual const char* GetName() override { return "enemy"; }

    virtual Vector2 GetPosition() { return m_position; }

    void OnCollision(ColliderComponent* pOtherCollider);
    
    virtual void Update(double deltaTime) override;

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual bool Move(Vector2 direction, float speedMultiplier) override;

    virtual bool doesDamage(ColliderComponent* pCollider) { return true; }

    virtual bool doesHeal(ColliderComponent* pCollider) { return false; }
};

