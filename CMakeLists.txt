# minimum cmake version
cmake_minimum_required(VERSION 3.1)

# project name and languages supported
project(space-invader CXX)

# set the sources
set(SOURCES
    main.cpp
    Window.cpp
    Game.cpp
    Gunship.cpp
    Invader.cpp
)

# find SFML library
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
set(SFML_LIBRARY sfml-system sfml-window sfml-graphics)

# Create executable
add_executable(space-invader-exe ${SOURCES})

# Link libraries
target_link_libraries(space-invader-exe PUBLIC ${SFML_LIBRARY})

# add library directories
target_include_directories(space-invader-exe PUBLIC ${SFML_INCLUDE_DIR})

# set executable location
set_target_properties(space-invader-exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")