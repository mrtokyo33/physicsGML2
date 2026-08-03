cmake_minimum_required(VERSION 3.20)    

project(Physics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)             
set(CMAKE_CXX_STANDARD_REQUIRED ON)     
set(CMAKE_CXX_EXTENSIONS OFF)           

find_package(SDL2 REQUIRED)  
find_package(SDL2_image REQUIRED)                       
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(Physics
    src/main.cpp
    src/drawing.cpp
    src/sdl_utils.cpp
    src/math/vector.cpp
    src/math/matrix.cpp
    src/math/quaternion.cpp
)

target_link_libraries(Physics PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    nlohmann_json::nlohmann_json
)