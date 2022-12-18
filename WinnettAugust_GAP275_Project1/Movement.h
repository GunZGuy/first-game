#pragma once
#include "GameObject.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "Vector2.h"
#include "StaticImage.h"
#include "StateGameOver.h"
#include "ExampleGame.h"
#include "HealthBar.h"
#include <sstream>
#include "UITextField.h"
#include "ParticleSystem.h"
#include "SDL_ttf.h"

class ExampleGame;
struct Mix_Chunk;

//Component housing all data regarding the player
class Movement :
    public GameObject
{
    using Vector2 = Vector2<float>;

private:
    //Player Model
    static constexpr int s_kpColor[] = { 0, 128, 0, SDL_ALPHA_OPAQUE };
    static constexpr int s_kWidth = 50;
    static constexpr int s_kHeight = 50;
    static constexpr double s_kSpeed = 100;

    double m_currentOffset;

    AnimationComponent m_animation;

    Vector2 m_position;

    Vector2 m_size;

    ColliderComponent m_collider;

    ExampleGame* m_pGame;

    HealthBar m_healthbar;

    Mix_Chunk* m_pWallSound;

    Mix_Chunk* m_pDamageSound;

    Mix_Chunk* m_pHealingSound;

    std::stringstream m_strm;

    SDL_Renderer* m_pRenderer;

    std::vector<GameObject*> m_gameObjects;

    UITextField* m_pText;

    ParticleSystem* m_pHealParticle;
    ParticleSystem* m_pDamageParticle;

    TTF_Font* m_pFont;
public:
    double health = m_healthbar.health;

    //Text Array for HealthBar
    char text[16];

    Movement(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee, ExampleGame* pGame);
    ~Movement();
    
    // Inherited via GameObject
    virtual void Update(double deltaTime) override;
    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual Vector2 GetPosition() override { return m_position; }

    AnimationComponent* GetAnimationComponent() { return &m_animation; }

    virtual const char* GetName() override { return "player"; }

    //bool for movement
    bool TryMove(Vector2 deltaPosition);

    void OnCollision(ColliderComponent* pOtherCollider);

    void SetPosition(Vector2 newPosition);

    //Get X and Y positions
    double GetX() const { return m_position.m_x; }
    double GetY() const { return m_position.m_y; }

    int m_direction;

    //Set Player Health
    void SetHealth(int x);
};