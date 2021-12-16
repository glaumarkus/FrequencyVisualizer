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

# find SDL
find_package(SDL2 REQUIRED)

if (TRUE)

# add executable
add_executable(
    ${TARGET} 
    # internal
    src/Color.cpp
    src/LEDController.cpp
    src/LEDVisualizer.cpp
    src/FFTVisualizer.cpp
    # app
    app.cpp 
    # for rpi
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/dma.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pwm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pcm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/rpihw.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/ws2811.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/mailbox.c
    )

# set includes
target_include_directories(
    ${TARGET} PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/dependencies/RaspberryPiAudio/include
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x
)

# link 
target_link_libraries( 
    ${TARGET} PUBLIC
    AudioLib
    ${SDL2_LIBRARIES} 
)

endif()

if (TRUE)

# add executable
add_executable(
    DEBUG 
    app2.cpp 
    # internal
    src/Color.cpp
    src/LEDController.cpp
    src/LEDVisualizer.cpp
    # for rpi
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/dma.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pwm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pcm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/rpihw.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/ws2811.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/mailbox.c
)

# set includes
target_include_directories(
    DEBUG PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x
    ${PROJECT_SOURCE_DIR}/dependencies/RaspberryPiAudio/include
)

# link 
target_link_libraries( 
    DEBUG PUBLIC
    AudioLib
)

endif()

if (TRUE)

# add executable
add_executable(
    LED_VISUALIZER 
    # internal
    src/Color.cpp
    src/LEDController.cpp
    src/LEDVisualizer.cpp
    src/LEDEnsemble.cpp
    # for rpi
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/dma.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pwm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/pcm.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/rpihw.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/ws2811.c
    ${PROJECT_SOURCE_DIR}/dependencies/rpi_ws281x/mailbox.c
    # main
    app3.cpp
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


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
