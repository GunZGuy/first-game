#pragma once
#include "GameObject.h"
#include "Movement.h"
#include "ColliderComponent.h"
#include "AnimationComponent.h"

class CollisionReferee;

class Boss :
    public GameObject
{
protected:
    using Vector2 = Vector2<float>;

    const float m_kDetectDistanceSqr;

    float m_kSpeed;

    GameObject* m_pTarget;

    AnimationComponent m_enemy;
    Vector2 m_position;
    Vector2 m_size;

private:
    ColliderComponent m_collider;

public:

    Boss(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee,
        float speed = 70, float detectionRadius = 100);
    ~Boss();

    float SetSpeed(float speed) { m_kSpeed *= 1.5; }

    virtual const char* GetName() override { return "enemy"; }

    virtual Vector2 GetPosition() { return m_position; }

    void OnCollision(ColliderComponent* pOtherCollider);

    virtual void Update(double deltaTime) override;

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual bool Move(Vector2 direction, float speedMultiplier) override;

    virtual bool doesDamage(ColliderComponent* pCollider) { return true; }

    virtual bool doesHeal(ColliderComponent* pCollider) { return false; }
};

