#pragma once

class GameObject;
class State;

//State Machine for all different enemy states
class AiStateMachine
{
public:
    enum StateName
    {
        None,
        Wander,
        Chase
    };
private:
    GameObject* m_pOwner;
    GameObject* m_pTarget;

    State* m_pCurrentState;

    StateName m_currentStateName;
public:
    AiStateMachine(GameObject* pOwner, GameObject* pTarget, StateName initialState);
    ~AiStateMachine();

    void Update(double deltaTime);
    
    void ChangeToState(StateName state);

    GameObject* GetOwner() { return m_pOwner; }
};