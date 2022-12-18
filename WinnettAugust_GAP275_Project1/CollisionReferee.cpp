#include "CollisionReferee.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include <time.h>
#include "Wall.h"
#include "Healing.h"

CollisionReferee::CollisionReferee()
{
}

CollisionReferee::~CollisionReferee()
{
}

void CollisionReferee::AddActiveCollider(ColliderComponent* pCollider)
{
    if (std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider) == m_activeColliders.end())
    {
        m_activeColliders.push_back(pCollider);
    }
}

void CollisionReferee::RemoveActiveCollider(ColliderComponent* pCollider)
{
    auto location = std::find(m_activeColliders.begin(), m_activeColliders.end(), pCollider);

    if (location != m_activeColliders.end())
    {
        m_activeColliders.erase(location);
    }
}

bool CollisionReferee::CheckForCollisionAndNotify(ColliderComponent* pColliderToCheck)
{
    bool isWall;
    bool didCollide = false;

    Vector2 colliderPosition = pColliderToCheck->GetPosition();
    Vector2 colliderSize = pColliderToCheck->GetSize();

    double left = colliderPosition.m_x;
    double right = left + colliderSize.m_x;
    double top = colliderPosition.m_y;
    double bottom = top + colliderSize.m_y;

    for (ColliderComponent* pOtherCollider : m_activeColliders)
    {
        if (pColliderToCheck == pOtherCollider)
            continue;

        Vector2 otherColliderPosition = pOtherCollider->GetPosition();
        Vector2 otherColliderSize = pOtherCollider->GetSize();

        double otherLeft = otherColliderPosition.m_x;
        double otherRight = otherLeft + otherColliderSize.m_x;
        double otherTop = otherColliderPosition.m_y;
        double otherBottom = otherTop + otherColliderSize.m_y;
        
        bool xOverlap = left < otherRight && right > otherLeft;

        bool yOverlap = top < otherBottom && bottom > otherTop;

        if (xOverlap && yOverlap)
        {
            didCollide = true;
            
            pColliderToCheck->GetOwner()->OnCollision(pOtherCollider);
            isWall = pOtherCollider->GetOwner()->isWall(pColliderToCheck);
            pOtherCollider->GetOwner()->OnCollision(pColliderToCheck);

            if (isWall == false)
            {
                return !didCollide;
            }
            else if(isWall = true)
            {
                return didCollide;
            }
        }
    }

    return didCollide;
}
