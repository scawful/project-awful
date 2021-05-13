# set the project name
project(awful)

# add the executable
add_executable(awful awful.cpp Game.cpp State/State.cpp State/MainMenuState.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(awful sfml-graphics sfml-audio sfml-network sfml-system sfml-audio)