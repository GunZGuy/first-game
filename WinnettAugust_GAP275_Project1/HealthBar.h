#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "SDL_ttf.h"
#include <vector>


class HealthBar :
    public GameObject
{
private:
    SDL_Rect m_transform;

    SDL_Texture* m_pTexture;

    std::vector<GameObject*> m_gameObjects;


public:
    //Player Health
    double health = 100;

    HealthBar();
    ~HealthBar();

    //Set Player Health
    void SetHealth(double x) { health = x; }

    //Returns health value
    double GetHealth() { return health; }

    virtual void Render(SDL_Renderer* pRenderer) override;
};

