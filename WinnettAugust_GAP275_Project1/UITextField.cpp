#include "UITextField.h"


UITextField::UITextField(TTF_Font* pFont, const char* pText, SDL_Color color, Vector2 position, SDL_Renderer* pRenderer, int wrap)
    : m_pTexture(nullptr)
    , m_pFont(pFont)
    , m_pText(pText)
    , m_color(color)
    , m_position(position)
    , m_pRenderer(pRenderer)
    , m_wrap(wrap)
{
    //Create surface
    SDL_Surface* pTextSurface = TTF_RenderText_Blended_Wrapped(pFont, pText, color, wrap);

    //Create Texture
    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);
    
    //Get dimensions and apply
    m_transform.x = (int)position.m_x;
    m_transform.y = (int)position.m_y;

    m_transform.w = pTextSurface->w;
    m_transform.h = pTextSurface->h;


    SDL_FreeSurface(pTextSurface);

}

UITextField::~UITextField()
{
    SDL_DestroyTexture(m_pTexture);
}

void UITextField::Render(SDL_Renderer* pRenderer)
{
    SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &m_transform);
}

void UITextField::Update(double deltaTime)
{
    //Create surface
    SDL_Surface* pTextSurface = TTF_RenderText_Blended_Wrapped(m_pFont, m_pText, m_color, m_wrap);

    //Create Texture
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTextSurface);

    //Get dimensions and apply
    m_transform.x = (int)m_position.m_x;
    m_transform.y = (int)m_position.m_y;

    m_transform.w = pTextSurface->w;
    m_transform.h = pTextSurface->h;


    SDL_FreeSurface(pTextSurface);

}
