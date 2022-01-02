#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>


struct LEDConfiguration
{
    LEDConfiguration();
    ~LEDConfiguration();

    bool LoadConfig(const std::string& path);

    int numLeds;
    uint8_t brightness;
    uint8_t max_brightness;

    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
    uint8_t state;

    float max_inc;
    float max_dec;

    int start;
    double exp;

};


