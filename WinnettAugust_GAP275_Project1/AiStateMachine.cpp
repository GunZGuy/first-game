#include "AiStateMachine.h"

#include "AiStateChase.h"
#include "AiStateWander.h"
#include "State.h"

AiStateMachine::AiStateMachine(GameObject* pOwner, GameObject* pTarget, StateName initialState)
    : m_pOwner(pOwner)
    , m_pTarget(pTarget)
    , m_pCurrentState(nullptr)
{
    ChangeToState(initialState);
}

AiStateMachine::~AiStateMachine()
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
    }
}

void AiStateMachine::Update(double deltaTime)
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Update(deltaTime);
    }
}

void AiStateMachine::ChangeToState(StateName state)
{
    if (m_currentStateName == state)
        return;
    
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
    }
    switch (state)
    {
    case StateName::None:
        m_pCurrentState = new State();
        break;
    case StateName::Wander:
        m_pCurrentState = new AiStateWander(this, 1);
        break;
    case StateName::Chase:
        m_pCurrentState = new AiStateChase(this, m_pTarget);
        break;
    }

    m_currentStateName = state;
    m_pCurrentState->Enter();
}