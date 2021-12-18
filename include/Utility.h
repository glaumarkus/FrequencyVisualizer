#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Color.h"


/*
* Timer class
*/
class Timer
{
public:

	Timer(std::string msg) :
		m_msg(std::move(msg)),
		m_tp(std::chrono::high_resolution_clock::now())
	{}

	~Timer()
	{
		auto duration = std::chrono::duration_cast<std::chrono::duration<double>>( std::chrono::high_resolution_clock::now() - m_tp) ;
		std::cout << "[TIMER]: " << m_msg << "\t" << duration.count() * 1000 << "ms" << "\n";
	}

    void Update(const std::string& msg)
    {
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>( std::chrono::high_resolution_clock::now() - m_tp) ;
		std::cout << "[TIMER]: " << msg << "\t" << duration.count() * 1000 << "ms" << "\n";
    }


private:

	std::string m_msg;
	std::chrono::high_resolution_clock::time_point m_tp;
};
