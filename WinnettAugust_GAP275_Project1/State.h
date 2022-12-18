#pragma once

class State
{
public:
    State() {}
    virtual ~State() {}

    virtual void Enter() {}

    virtual void Update(double deltaTime) {}

    virtual void Exit() {}

};