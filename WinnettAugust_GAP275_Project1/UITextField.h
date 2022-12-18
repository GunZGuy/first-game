#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "SDL_ttf.h"


class UITextField :
    public GameObject
{
    using Vector2 = Vector2<float>;

private:
    SDL_Rect m_transform;

    SDL_Texture* m_pTexture;

    TTF_Font* m_pFont;

    const char* m_pText;

    SDL_Color m_color;

    Vector2 m_position;

    SDL_Renderer* m_pRenderer;

    int m_wrap;
public:
    UITextField(TTF_Font* pFont, const char* pText, SDL_Color color, Vector2 position, SDL_Renderer* pRenderer, int wrap);
    ~UITextField();

    virtual void Render(SDL_Renderer* pRenderer) override;

    virtual void Update(double deltaTime) override;

};

