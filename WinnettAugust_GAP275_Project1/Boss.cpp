#include "Boss.h"
#include <iostream>
#include "SDL_image.h"
#include "AnimationComponent.h"

Boss::Boss(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee,
    float speed, float detectionRadius)
    : m_kSpeed(speed)
    , m_kDetectDistanceSqr(detectionRadius* detectionRadius)
    , m_pTarget(pTarget)
    , m_position(position)
    , m_size(size)
    , m_collider(this, SDL_Rect{ (int)position.m_x, (int)position.m_y, (int)size.m_x, (int)size.m_y }, pReferee)
    , m_enemy("assets/boss.png", 12, 100, 100, 3, pRenderer)

{
    //Animations available
    m_enemy.AddAnimationSequence("green", 0, 0);
    m_enemy.AddAnimationSequence("yellow", 1, 1);
    m_enemy.AddAnimationSequence("red", 2, 2);
    m_enemy.PlayAnimation("idle");
}

Boss::~Boss()
{

}

void Boss::OnCollision(ColliderComponent* pOtherCollider)
{
}

void Boss::Update(double deltaTime)
{
    Vector2 pathToTarget = m_pTarget->GetPosition() - this->GetPosition();

    if (pathToTarget.GetSquareLength() <= m_kDetectDistanceSqr)
    {
        Vector2 directionToTarget = pathToTarget.GetNormalized();
        Move(directionToTarget, (float)deltaTime);

    }

    m_enemy.m_transform.x = (int)m_position.m_x;
    m_enemy.m_transform.y = (int)m_position.m_y;
    m_enemy.Update(deltaTime);

}

void Boss::Render(SDL_Renderer* pRenderer)
{
    m_enemy.Render(pRenderer);
}

//Boss Movement
bool Boss::Move(Vector2 direction, float speedMultiplier)
{
    Vector2 deltaPosition = direction * speedMultiplier * m_kSpeed;

    bool didMove = m_collider.TryMove(deltaPosition);

    if (didMove)
    {
        m_position.m_x += deltaPosition.m_x;
        m_position.m_y += deltaPosition.m_y;
        m_collider.SetPosition(m_position);
    }

    return didMove;
}
