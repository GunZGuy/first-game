#include "ParticleSystem.h"
#include <random>
#include <iostream>
ParticleSystem::ParticleSystem(SDL_Renderer* pRenderer, Vector2<float> centerPoint, int particleCount,
    float maxSpeed, float radius, SDL_Surface* imageSurface)
    : m_kCenterPoint(centerPoint)
    , m_kParticleCount(particleCount)
    , m_kRadiusSqr(radius* radius)
    , m_pParticles(new Particle[particleCount])
    , m_pImageSurface(imageSurface)
    , m_pTexture()
{
    //Randomize velocities
    std::random_device device;
    std::mt19937 twister;
    twister.seed(device());
    std::uniform_real_distribution<float> random(-1, 1);
    for (int i = 0; i < particleCount; ++i)
    {
        //Initialize position.
        m_pParticles[i].m_positionOffset = Vector2<float>{ 0, 0 };

        //Randomize velocities
        m_pParticles[i].m_velocity = Vector2<float>{ random(twister), random(twister) } * maxSpeed;
        m_pParticles[i].m_velocityBackup = m_pParticles[i].m_velocity;
    }

    if (imageSurface == nullptr)
    {
        std::cout << "Image Load Error : " << SDL_GetError() << std::endl;
        return;
    }


    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, imageSurface);
    if (m_pTexture == nullptr)
    {
        std::cout << "Texture Load Error : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(imageSurface);
}

//Destructor
ParticleSystem::~ParticleSystem()
{
    delete[] m_pParticles;
}

//Update object state
void ParticleSystem::Update(double deltaTime)
{

    if (particleSwitch == true)
    {
        //Loop Particle Array
        for (int i = 0; i < m_kParticleCount; ++i)
        {
            //Update each particles position
            m_pParticles[i].m_velocity = m_pParticles[i].m_velocityBackup;
            m_pParticles[i].m_positionOffset.m_x += m_pParticles[i].m_velocity.m_x * (float)deltaTime;
            m_pParticles[i].m_positionOffset.m_y += m_pParticles[i].m_velocity.m_y * (float)deltaTime;

            //If particle is outside radius, reset
            if (m_pParticles[i].m_positionOffset.GetSquareLength() >= m_kRadiusSqr)
            {
                m_pParticles[i].m_positionOffset = Vector2<float>{ 0,0 };
            }
        }
        if (timeout <= 0)
        {
            timeout = 0;

        }
        else
        {
            timeout -= deltaTime;
        }
    }
    else
    {
        for (int i = 0; i < m_kParticleCount; ++i)
        {
            //Update each particles position
            m_pParticles[i].m_positionOffset.m_x = 0;
            m_pParticles[i].m_positionOffset.m_y = 0;
        }
    }
}

//Render object
void ParticleSystem::Render(SDL_Renderer* pRenderer)
{
    if (particleSwitch == true && timeout > 0)
    {
        //Loop through particles
        for (int i = 0; i < m_kParticleCount; ++i)
        {
            Particle& particle = m_pParticles[i];
            Vector2<float>& particlePosition = particle.m_positionOffset;

            SDL_Rect particleTransform{ (m_kCenterPoint.m_x + particlePosition.m_x),
                (m_kCenterPoint.m_y + particlePosition.m_y), 10, 10 };

            SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &particleTransform);
        }
    }
    else
    {
        for (int i = 0; i < m_kParticleCount; ++i)
        {
            //Update each particles position
            m_pParticles[i].m_positionOffset.m_x = 0;
            m_pParticles[i].m_positionOffset.m_y = 0;
        }
    }
}

