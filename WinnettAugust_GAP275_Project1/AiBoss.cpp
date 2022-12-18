#include "AiBoss.h"

AiBoss::AiBoss(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee, 
    float speed, float detectionRadius)
    : Boss(pRenderer, position, size, pTarget, pReferee, speed, detectionRadius)
    , m_stateMachine(this, pTarget, AiStateMachine::StateName::None)
{

}

AiBoss::~AiBoss()
{
}

void AiBoss::Update(double deltaTime)
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    //Manually Set Boss Health
    if (keystate[SDL_SCANCODE_1])
    {
        SetHealth(100);
    }
    if (keystate[SDL_SCANCODE_2])
    {
        SetHealth(99);
    }
    if (keystate[SDL_SCANCODE_3])
    {
        SetHealth(40);
    }
    if (keystate[SDL_SCANCODE_4])
    {
        SetHealth(10);
    }

    Vector2 pathToTarget = m_pTarget->GetPosition() - this->GetPosition();
    //Boss Attack States - Health Based
    if (m_kHealth == 100)
    {
        m_enemy.PlayAnimation("green");
        m_stateMachine.ChangeToState(AiStateMachine::StateName::None);
    }
    else if (m_kHealth >= 50 && m_kHealth <= 99)
    {
        m_enemy.PlayAnimation("green");
        if (pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr)
        {
            m_stateMachine.ChangeToState(AiStateMachine::StateName::Chase);
        }
        else
        {
            m_stateMachine.ChangeToState(AiStateMachine::StateName::None);
        }
    }
    else if (m_kHealth <= 49 && m_kHealth >= 20)
    {
        m_enemy.PlayAnimation("yellow");
        if (pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr)
        {
            m_stateMachine.ChangeToState(AiStateMachine::StateName::Chase);
        }
        else
        {
            m_stateMachine.ChangeToState(AiStateMachine::StateName::Wander);
        }

    }
    else if (m_kHealth <= 19 && m_kHealth >= 1)
    {
        m_enemy.PlayAnimation("red");
        if (pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr * 3)
        {

            m_stateMachine.ChangeToState(AiStateMachine::StateName::Chase);
        }
    }


    //Animation
    m_enemy.m_transform.x = (int)m_position.m_x;
    m_enemy.m_transform.y = (int)m_position.m_y;
    m_enemy.Update(deltaTime);


    m_stateMachine.Update(deltaTime);
}
