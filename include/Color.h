#pragma once

#include "LED_common.h"

/*
* Conversion of RGB Values to LED values
*/
struct Color
{
    Color();
    Color(const float& f);
    Color(const float& r, const float& g, const float& b);

    operator int();
    operator uint32_t();
    
    Color& operator +=(const float& f);
    Color& operator +=(const Color& other);
    Color& operator -=(const float& f);
    Color& operator -=(const Color& other);
    Color& operator *=(const float& f);
    Color& operator *=(const Color& other);
    Color& operator /=(const float& f);
    Color& operator /=(const Color& other);
    
    float r;
    float g;
    float b;

};

Color operator +(const Color& first, const float& f);
Color operator -(const Color& first, const float& f);
Color operator *(const Color& first, const float& f);
Color operator /(const Color& first, const float& f);

Color operator +(const Color& first, const Color& second);
Color operator -(const Color& first, const Color& second);
Color operator *(const Color& first, const Color& second);
Color operator /(const Color& first, const Color& second);

float ApplyLimit(const float& f, const float& lower, const float& upper);

static Color Black(0.0f);
static Color White(1.0f);

static uint32_t uBlack = static_cast<uint32_t>(Black);
static uint32_t uWhite = static_cast<uint32_t>(White);