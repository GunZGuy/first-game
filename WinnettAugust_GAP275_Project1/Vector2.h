#pragma once

template<class NumberType>
struct Vector2
{
public:
    NumberType m_x;
    NumberType m_y;

    //Overload *
    Vector2 operator*(float right)
    {
        return Vector2{ m_x * right, m_y * right };
    }

    //Overload -
    Vector2 operator-(Vector2 b)
    {
        return Vector2{ this->m_x - b.m_x, this->m_y - b.m_y };
    }

    //Squared Length
    NumberType GetSquareLength()
    {
        return m_x * m_x + m_y * m_y;
    }

    //Normalize length
    Vector2 GetNormalized()
    {
        float length = sqrtf(GetSquareLength());

        if (length == 0)
            return Vector2{ 0,0 };
        else
            return Vector2{ m_x / length, m_y / length };
    }
};


