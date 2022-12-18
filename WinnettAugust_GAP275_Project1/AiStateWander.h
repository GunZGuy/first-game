#pragma once
#include "State.h"
#include "Vector2.h"
#include "RNG.h"

class AiStateMachine;
class RNG;

//State For Enemy Wandering
class AiStateWander :
    public State
{
private:
    const double m_kDirectionChangeInterval;

    AiStateMachine* m_pOwner;

    bool m_doMove;

    Vector2<float> m_currentDirection;

    double m_timeUntilDirectionChange;

    RNG* randomNumber;

public:
    AiStateWander(AiStateMachine* pOwner, double directionChangeInterval);
    ~AiStateWander();

    virtual void Update(double deltaTime) override;

    //Allow Random Direction Wandering
    void RandomizeDirection();
};

