cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fpermissive")

set (TARGET SDL_Visualizer)
project(${TARGET} VERSION 0.1.0)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cmake)

include(CTest)
enable_testing()

# add submodule
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/dependencies/RaspberryPiAudio
)

if (FALSE)

# add executable
add_executable(
    LED_VISUALIZER 
    # internal
    src/configreader.cpp
    src/Color.cpp
    src/LEDController.cpp
    src/LEDVisualizer.cpp
    src/LEDEnsemble.cpp
    src/SerialReader.cpp
    src/SerialMessage.cpp
    # for rpi
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/dma.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pwm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pcm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/rpihw.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/ws2811.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/mailbox.c
    # main
    app.cpp
)

# set includes
target_include_directories(
    LED_VISUALIZER PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x
    ${PROJECT_SOURCE_DIR}/dependencies/RaspberryPiAudio/include
)

# link 
target_link_libraries( 
    LED_VISUALIZER PUBLIC
    AudioLib
)

endif()

add_executable(SS serialtest.cpp src/SerialMessage.cpp src/SerialReader.cpp)
# set includes
target_include_directories(
    SS PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
