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



LEDConfiguration::LEDConfiguration()
{}

LEDConfiguration::~LEDConfiguration()
{}

bool LEDConfiguration::LoadConfig(const std::string& path)
{

    std::ifstream file_(path);

    if (!file_.is_open()) {
      std::cerr << "Config file not found!" << std::endl;
      return false;
    }

    std::string line_;
    int i = 0;

    while (getline(file_, line_)) 
    {
        if (line_[0] == '#') continue;
        if (line_.empty()) continue;

        std::stringstream param(line_);
        std::string paramName;

        param >> paramName;
        if (paramName == "numLeds")
            param >> numLeds;
        else if (paramName == "brightness") 
            param >> brightness;
        else if (paramName == "max_brightness") 
            param >> max_brightness;
        else if (paramName == "state") 
            param >> state;
        else if (paramName == "red") 
            param >> red;
        else if (paramName == "green") 
            param >> green; 
        else if (paramName == "blue") 
            param >> blue;   
        else if (paramName == "max_inc") 
            param >> max_inc;   
        else if (paramName == "max_dec") 
            param >> max_dec;   
        else if (paramName == "start") 
            param >> start;   
        else if (paramName == "exp") 
            param >> exp;      
        else 
            std::cerr << "Unrecognized pipeline parameter: " << paramName << std::endl;
    }
    file_.close();
    return true;
}

