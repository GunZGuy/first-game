#include "Movement.h"
#include <iostream>
#include <SDL_image.h>
#include "AnimationComponent.h"
#include <chrono>
#include <thread>
#include <time.h>
#include "ExampleGame.h"
#include "StaticImage.h"
#include "StateGameOver.h"
#include "HealthBar.h"
#include "UITextField.h"
#include "ParticleSystem.h"



Movement::Movement(SDL_Renderer* pRenderer, SDL_Rect transform, CollisionReferee* pReferee, ExampleGame* pGame)
    : m_currentOffset(0)
    , m_direction(0)
    , m_position{(float)transform.x, (float)transform.y}
    , m_size{ (float)transform.w, (float)transform.h }
    , m_animation("assets/spritesheet.png", 12, 32, 32, 15, pRenderer)
    , m_collider(this, transform, pReferee)
    , m_pGame(pGame)
    , m_pRenderer(pRenderer)
{

    m_animation.AddAnimationSequence("idle", 8, 8);
    m_animation.AddAnimationSequence("runup", 0, 3);
    m_animation.AddAnimationSequence("runleft", 4, 7);
    m_animation.AddAnimationSequence("rundown", 8, 11);
    m_animation.AddAnimationSequence("runright", 12, 15);

    m_pWallSound = Mix_LoadWAV("assets/wallsound.wav");
    m_pDamageSound = Mix_LoadWAV("assets/damage.wav");
    m_pHealingSound = Mix_LoadWAV("assets/healing.wav");
    if (m_pWallSound == nullptr || m_pDamageSound == nullptr || m_pHealingSound == nullptr)
    {
        std::cout << "Failed to load sound. Error: " << SDL_GetError() << std::endl;
    }
    Mix_VolumeChunk(m_pWallSound, 5);
    Mix_VolumeChunk(m_pDamageSound, 5);
    Mix_VolumeChunk(m_pHealingSound, 1);

    m_pHealParticle = new ParticleSystem(pRenderer, Vector2{ (float)m_position.m_x,(float)m_position.m_y}, 32, 40, 50, IMG_Load("assets/healSprite.png"));
    m_gameObjects.push_back(m_pHealParticle);

    m_pDamageParticle = new ParticleSystem(pRenderer, Vector2{ (float)m_position.m_x, (float)m_position.m_y }, 32, 40, 50, IMG_Load("assets/damageSprite.png"));
    m_gameObjects.push_back(m_pDamageParticle);

    sprintf_s(text, "HP : %d / %d", (int)m_healthbar.GetHealth(), 10);
    m_pText = new UITextField(TTF_OpenFont("assets/arial.ttf", 20), text, SDL_Color{ 255, 0, 0 }, Vector2{ 350,0 }, m_pRenderer, 1000);
    m_gameObjects.push_back(m_pText);
}

Movement::~Movement()
{
    if (m_pWallSound != nullptr)
    {
        Mix_FreeChunk(m_pWallSound);
        m_pWallSound = nullptr;
    }
    if (m_pDamageSound != nullptr)
    {
        Mix_FreeChunk(m_pDamageSound);
        m_pDamageSound = nullptr;
    }
    if (m_pHealingSound != nullptr)
    {
        Mix_FreeChunk(m_pHealingSound);
        m_pHealingSound = nullptr;
    }
}


void Movement::Update(double deltaTime)
{
    //Set text array
    sprintf_s(text, "HP : %d / %d", (int)health, 100);

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    //Movement with Vector2
    if (keystate[SDL_SCANCODE_A])
    {
        if (keystate[SDL_SCANCODE_S])
        {
            TryMove(Vector2{ -0.04f, 0.04f });
            m_animation.PlayAnimation("rundown");
        }
        else if (keystate[SDL_SCANCODE_W])
        {
            TryMove(Vector2{ -0.04f, -0.04f });
            m_animation.PlayAnimation("runup");
        }
        else
        {
            TryMove(Vector2{ -0.04f, 0 });
            m_animation.PlayAnimation("runleft");
        }
    }
    else if (keystate[SDL_SCANCODE_D])
    {
        if (keystate[SDL_SCANCODE_S])
        {
            TryMove(Vector2{ 0.04f, 0.04f });
            m_animation.PlayAnimation("rundown");
        }
        else if (keystate[SDL_SCANCODE_W])
        {
            TryMove(Vector2{ 0.04f, -0.04f });
            m_animation.PlayAnimation("runup");
        }
        else
        {
            TryMove(Vector2{ 0.04f, 0 });
            m_animation.PlayAnimation("runright");
        }
    }
    else if (keystate[SDL_SCANCODE_W])
    {
        TryMove(Vector2{ 0, -0.04f });
        m_animation.PlayAnimation("runup");
    }
    else if (keystate[SDL_SCANCODE_S])
    {
        TryMove(Vector2{ 0, 0.04f });
        m_animation.PlayAnimation("rundown");
    }
    else
    {
        m_animation.PlayAnimation("idle");
    }
    m_animation.m_transform.x = (int)m_position.m_x;
    m_animation.m_transform.y = (int)m_position.m_y;

    //Updates for different components
    m_animation.Update(deltaTime);
    m_pHealParticle->Update(deltaTime);
    m_pDamageParticle->Update(deltaTime);
    m_pText->Update(deltaTime);

    //If health is 0, GAME OVER
    if (health < 1)
    {
        m_pGame->LoadScene(ExampleGame::GameOver);
    }

}

void Movement::Render(SDL_Renderer* pRenderer)
{
    m_animation.Render(pRenderer);
    for (GameObject* pObject : m_gameObjects)
    {
        pObject->Render(pRenderer);
    }
}

bool Movement::TryMove(Vector2 deltaPosition)
{
    bool didMove = m_collider.TryMove(deltaPosition);

    if (didMove)
    {
        m_position.m_x += deltaPosition.m_x;
        m_position.m_y += deltaPosition.m_y;
    }
    return didMove;
}

void Movement::OnCollision(ColliderComponent* pOtherCollider)
{
    //Check if collider does damage or heal
    const char* colliderName = pOtherCollider->GetOwner()->GetName();
    bool doesHeal = pOtherCollider->GetOwner()->doesHeal(pOtherCollider);
    bool doesDamage = pOtherCollider->GetOwner()->doesDamage(pOtherCollider);

    std::cout << "Collided with " << colliderName << std::endl;
    
    //Does Healing
    if (doesHeal == true && health < 100)
    {
        health += 0.01f;
        m_healthbar.SetHealth(health);
        m_pHealParticle->particleSwitch = true;
        m_pHealParticle->timeout = 1.0f;
        m_pHealParticle->SetPosition(m_position.m_x + 10, m_position.m_y + 10);
    }
    //Does Damage
    else if(doesDamage == true && health > 0)
    {
        health -= 0.01f;
        m_healthbar.SetHealth(health);
        m_pDamageParticle->particleSwitch = true;
        m_pDamageParticle->timeout = 1.0f;
        m_pDamageParticle->SetPosition(m_position.m_x, m_position.m_y);
    }
    //If does NOT heal or hurt IE: Wall
    if (!doesDamage && !doesHeal)
    {
        Mix_PlayChannel(-1, m_pWallSound, 0);
    }

    if (doesDamage)
    {
        Mix_PlayChannel(-1, m_pDamageSound, 0);
    }

    if (doesHeal)
    {
        Mix_PlayChannel(-1, m_pHealingSound, 0);
    }
}

void Movement::SetPosition(Vector2 newPosition)
{
    m_position.m_x = newPosition.m_x;
    m_position.m_y = newPosition.m_y;

    m_collider.SetPosition(newPosition);
}

void Movement::SetHealth(int x)
{
    health = x;
}


