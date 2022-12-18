#include "AiStateMachineEnemy.h"

AiStateMachineEnemy::AiStateMachineEnemy(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* 
    pReferee, float speed, float detectionRadius)
    : Enemy(pRenderer,position, size, pTarget, pReferee, speed, detectionRadius)
    , m_stateMachine(this, pTarget, AiStateMachine::StateName::Wander)
{
    
}

AiStateMachineEnemy::~AiStateMachineEnemy()
{
}

void AiStateMachineEnemy::Update(double deltaTime)
{
    Vector2 pathToTarget = m_pTarget->GetPosition() - this->GetPosition();

    if (pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr)
    {
        m_stateMachine.ChangeToState(AiStateMachine::StateName::Chase);
    }
    else
    {
        m_stateMachine.ChangeToState(AiStateMachine::StateName::Wander);
    }

    //Animation
    m_enemy.m_transform.x = (int)m_position.m_x;
    m_enemy.m_transform.y = (int)m_position.m_y;
    m_enemy.Update(deltaTime);


    m_stateMachine.Update(deltaTime);
}
