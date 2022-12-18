#include "AiStateChase.h"
#include "AiStateMachine.h"
#include "GameObject.h"

AiStateChase::AiStateChase(AiStateMachine* pOwner, GameObject* pTarget)
    : m_pOwner(pOwner)
    , m_pTarget(pTarget)
{
}

AiStateChase::~AiStateChase()
{
}

void AiStateChase::Update(double deltaTime)
{
    using Vector2 = Vector2<float>;
    Vector2 pathToTarget = m_pTarget->GetPosition() - m_pOwner->GetOwner()->GetPosition();

    pathToTarget = pathToTarget.GetNormalized();
    m_pOwner->GetOwner()->Move(pathToTarget, (float)deltaTime);


}
