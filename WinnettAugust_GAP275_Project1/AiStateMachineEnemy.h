#pragma once
#include "Enemy.h"
#include "AiStateMachine.h"

//State Machine for Enemies
class AiStateMachineEnemy :
    public Enemy
{
private:
    AiStateMachine m_stateMachine;

public:
    //AI Enemy Information - Position, collision, AOE
    AiStateMachineEnemy(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee,
        float speed = 70, float detectionRadius = 100);
    ~AiStateMachineEnemy();

    virtual void Update(double deltaTime) override;
};

