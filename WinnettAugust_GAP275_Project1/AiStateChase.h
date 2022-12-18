#pragma once
#include "State.h"

class AiStateMachine;
class GameObject;

//AI Chasing State
class AiStateChase :
    public State
{
private:
    AiStateMachine* m_pOwner;

    GameObject* m_pTarget;
public:
    AiStateChase(AiStateMachine* pOwner, GameObject* pTarget);
    ~AiStateChase();

    virtual void Update(double deltaTime) override;
};

