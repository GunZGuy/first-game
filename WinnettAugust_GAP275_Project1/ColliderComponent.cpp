#include "ColliderComponent.h"
#include "CollisionReferee.h"
#include <string>

ColliderComponent::ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee)
    : m_pOwner(pOwner)
    , m_position{ (float)transform.x, (float)transform.y }
    , m_size{ (float)transform.w, (float)transform.h }
    , m_pReferee(pReferee)
{
    if (pReferee != nullptr)
    {
        pReferee->AddActiveCollider(this);
    }
}

ColliderComponent::~ColliderComponent()
{
    if (m_pReferee != nullptr)
    {
        m_pReferee->RemoveActiveCollider(this);
    }
}

bool ColliderComponent::TryMove(Vector2 deltaPosition)
{

    if (m_pReferee == nullptr)
    {
        return true;
    }

    m_position.m_x += deltaPosition.m_x;
    m_position.m_y += deltaPosition.m_y;

    //Check for collision , create bool based on return value
    bool didCollide = m_pReferee->CheckForCollisionAndNotify(this);

    //If collision happened, set position back by to previous location. Else do nothing
    if (didCollide == true)
    {
        m_position.m_x -= deltaPosition.m_x;
        m_position.m_y -= deltaPosition.m_y;
    }

    return !didCollide;
}