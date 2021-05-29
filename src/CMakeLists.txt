#Cmake version
cmake_minimum_required(VERSION 3.10)

# set the project name
project(awful VERSION 1.0)

# add the executable
add_executable(awful awful.cpp Game.cpp State/State.cpp State/MainMenuState.cpp State/GameState.cpp Actor/Actor.cpp Actor/Player.cpp Components/MovementComponent.cpp)
include_directories("../assets")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find the sfml library 
find_package(SFML 2.5 COMPONENTS graphics audio network system audio REQUIRED)
target_link_libraries(awful sfml-graphics sfml-audio sfml-network sfml-system sfml-audio)

set (source "${CMAKE_SOURCE_DIR}/assets")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
)
