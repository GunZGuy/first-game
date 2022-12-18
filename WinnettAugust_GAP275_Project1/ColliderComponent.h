#pragma once
#include <SDL.h>
#include "Vector2.h"

class GameObject;
class CollisionReferee;

//Component housing collider
class ColliderComponent
{
    using Vector2 = Vector2<float>;

private:
    GameObject* m_pOwner;

    Vector2 m_position;
    Vector2 m_size;

    CollisionReferee* m_pReferee;
public:
    ColliderComponent(GameObject* pOwner, SDL_Rect transform, CollisionReferee* pReferee);
    ~ColliderComponent();

    GameObject* GetOwner() { return m_pOwner; }

    Vector2 GetPosition() { return m_position; }

    Vector2 GetSize() { return m_size; }

    void SetPosition(Vector2 newPosition) { m_position = newPosition; }

    void SetSize(Vector2 newSize) { m_size = newSize; }

    bool TryMove(Vector2 deltaPosition);
};

