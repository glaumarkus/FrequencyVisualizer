#include <Color.h>


Color::Color() :
    r(0.0f),
    g(0.0f),
    b(0.0f)
{}


Color::Color(const float& f) :
    r(f),
    g(f),
    b(f)
{}

Color::Color(const float& r, const float& g, const float& b) :
    r(r),
    g(g),
    b(b)
{}



Color::operator int()
{
    return 0;
}


Color::operator uint32_t() 
{
    uint32_t ret = 
    (uint8_t)0 << 24 | 
    (uint8_t)(ApplyLimit(r, 0.0f, 1.0f) * 255.9f) << 16 |
    (uint8_t)(ApplyLimit(g, 0.0f, 1.0f) * 255.9f) << 8 | 
    (uint8_t)(ApplyLimit(b, 0.0f, 1.0f) * 255.9f);
    return ret;
}


Color& Color::operator +=(const float& f)
{
    r += f;
    g += f;
    b += f;
    return *this;
}

Color& Color::operator +=(const Color& other)
{
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color& Color::operator -=(const float& f)
{
    r -= f;
    g -= f;
    b -= f;
    return *this;
}

Color& Color::operator -=(const Color& other)
{
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
}

Color& Color::operator *=(const float& f)
{
    r *= f;
    g *= f;
    b *= f;
    return *this;
}

Color& Color::operator *=(const Color& other)
{
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
}

Color& Color::operator /=(const float& f)
{
    r /= f;
    g /= f;
    b /= f;
    return *this;
}

Color& Color::operator /=(const Color& other)
{
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
}

Color operator +(const Color& first, const float& f)
{
   return Color(first.r + f, first.g + f, first.b + f);  
}

Color operator -(const Color& first, const float& f)
{
   return Color(first.r - f, first.g - f, first.b - f);  
}

Color operator *(const Color& first, const float& f)
{
   return Color(first.r * f, first.g * f, first.b * f);  
}

Color operator /(const Color& first, const float& f)
{
   return Color(first.r / f,first.g / f,first.b / f);  
}

Color operator +(const Color& first, const Color& second)
{
    return Color(first.r + second.r, first.g + second.g, first.b + second.b);
}

Color operator -(const Color& first, const Color& second)
{
    return Color(first.r - second.r, first.g - second.g, first.b - second.b);
}

Color operator *(const Color& first, const Color& second)
{
    return Color(first.r * second.r, first.g * second.g, first.b * second.b);
}

Color operator /(const Color& first, const Color& second)
{
    return Color(first.r / second.r, first.g / second.g, first.b / second.b);
}

float ApplyLimit(const float& f, const float& lower, const float& upper)
{
    return f > 1.0f ? 1.0f : (f < 0.0f ? 0.0f : f);
}

