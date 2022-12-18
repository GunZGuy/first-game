#include "AiStateWander.h"
#include "AiStateMachine.h"
#include "GameObject.h"
#include <random>

AiStateWander::AiStateWander(AiStateMachine* pOwner, double directionChangeInterval)
    : m_kDirectionChangeInterval(directionChangeInterval)
    , m_pOwner(pOwner)
    , m_doMove(false)
    , m_timeUntilDirectionChange(directionChangeInterval)
{
}

AiStateWander::~AiStateWander()
{
}

void AiStateWander::Update(double deltaTime)
{
    m_timeUntilDirectionChange -= deltaTime;
    if (m_timeUntilDirectionChange <= 0)
    {
        m_timeUntilDirectionChange = m_kDirectionChangeInterval;

        m_doMove = !m_doMove;
        if (m_doMove)
            RandomizeDirection();
    }
    if (m_doMove)
    {
        m_pOwner->GetOwner()->Move(m_currentDirection, (float)deltaTime);
    }
}

void AiStateWander::RandomizeDirection()
{
    m_currentDirection.m_x = (randomNumber->RandomNumberMovement());
    m_currentDirection.m_y = (randomNumber->RandomNumberMovement());
}
