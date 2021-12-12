#pragma once

#include <stdint.h>
#include <vector>

// dependencies
#include <Audio.h>

// external
#ifdef __arm__

#include <wiringPiI2C.h>
#include <ws2811.h>

#endif


// number of bars
constexpr int BINS = 40;
// pixelbuffer of bar
constexpr int BIN_MARGIN = 2;

// for calculating colors
constexpr float PI = 3.141592f;

// max increase
constexpr float MAX_INC = 0.3f;
// max decrease
constexpr float MAX_DECAY = -0.05f;
// bins to skip
constexpr int START = 5;
// scale of grouping bins
constexpr float SCALE_EXP = 1.45f;

