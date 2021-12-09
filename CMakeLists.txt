cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
find_package(SDL2_ttf REQUIRED)


# add executable
add_executable(${TARGET} app.cpp src/FFTVisualizer.cpp)

# set includes
target_include_directories(
    ${TARGET} PUBLIC
    ${SDL2_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/dependencies/RaspberryPiAudio/include()
)

# link 
target_link_libraries( 
    ${TARGET} PUBLIC
    AudioLib
    ${SDL2_LIBRARIES} 
    SDL2_ttf
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
