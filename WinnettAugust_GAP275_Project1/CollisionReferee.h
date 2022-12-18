#pragma once
#include <vector>
#include "Movement.h"

class ColliderComponent;
class Healing;

class CollisionReferee
{
    using Vector2 = Vector2<float>;

private:
    std::vector<ColliderComponent*> m_activeColliders;

public:
    CollisionReferee();
    ~CollisionReferee();

    void AddActiveCollider(ColliderComponent* pCollider);

    void RemoveActiveCollider(ColliderComponent* pCollider);

    bool CheckForCollisionAndNotify(ColliderComponent* pColliderToCheck);
};

