#pragma once
#include "GameObject.h"
#include "Vector2.h"


//Particle Source
class ParticleSystem :
    public GameObject
{
private:
    //Individual Particles
    struct Particle
    {
        Vector2<float> m_positionOffset;
        Vector2<float> m_velocity;
        Vector2<float> m_velocityBackup;
    };
private:
    //Particle Source Center Point
     Vector2<float> m_kCenterPoint;

    //Number of particles in instance
    const float m_kParticleCount;

    //Square of the maximum distance particles can travel
    const float m_kRadiusSqr;
    
    //Array of particles
    Particle* m_pParticles;

    SDL_Surface* m_pImageSurface;
    SDL_Texture* m_pTexture;

public:
    ParticleSystem(SDL_Renderer* pRenderer, Vector2<float> centerPoint, int particleCount, float maxSpeed, float radius, SDL_Surface* pImageSurface);
    ~ParticleSystem();

    virtual const char* GetName() override { return "Particle System"; }

    virtual void Update(double deltaTime) override;

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual Vector2<float> GetPosition() override { return m_kCenterPoint; }

    float SetPosition(float x, float y) { return m_kCenterPoint.m_x = x, m_kCenterPoint.m_y = y; }

    bool particleSwitch = false;
    double timeout = 5;
};

