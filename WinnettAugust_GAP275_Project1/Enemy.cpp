#include "Enemy.h"
#include <iostream>

Enemy::Enemy(SDL_Renderer* pRenderer, Vector2 position, Vector2 size, GameObject* pTarget, CollisionReferee* pReferee, 
    float speed, float detectionRadius)
    : m_kSpeed(speed)
    , m_kDetectDistanceSqr(detectionRadius * detectionRadius)
    , m_pTarget(pTarget)
    , m_position(position)
    , m_size(size)
    , m_collider(this, SDL_Rect{(int)position.m_x, (int)position.m_y, (int)size.m_x, (int)size.m_y}, pReferee)
    , m_enemy("assets/enemy.png", 12, 32, 32, 11, pRenderer)
{
    m_enemy.AddAnimationSequence("idle", 0, 0);
    m_enemy.AddAnimationSequence("walkright", 6, 8);
    m_enemy.AddAnimationSequence("walkleft", 9, 11);

    m_enemy.PlayAnimation("idle");
}

Enemy::~Enemy()
{
}

void Enemy::Update(double deltaTime)
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

void Enemy::Render(SDL_Renderer* pRenderer)
{

    m_enemy.Render(pRenderer);
}


void Enemy::OnCollision(ColliderComponent* pOtherCollider)
{
    
}


bool Enemy::Move(Vector2 direction, float speedMultiplier)
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