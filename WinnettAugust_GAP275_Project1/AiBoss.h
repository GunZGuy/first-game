#pragma once
#include "Boss.h"
#include "AiStateMachine.h"

class AiBoss :
    public Boss
{
private:
    AiStateMachine m_stateMachine;
    float m_kHealth = 100;

public:
    //Boss AI - Movement, collision, ability
    AiBoss(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee,
        float speed = 90, float detectionRadius = 100);

    //Sets Boss Health
    void SetHealth(float health) { m_kHealth = health; }

    ~AiBoss();

    virtual void Update(double deltaTime) override;
};

