#include "World.hpp"

/**
 * @brief Initialize any textures to be used in any World
 * @author @scawful
 * 
 */
void World::initTextures() 
{
    
}

/**
 * @brief Construct a new World:: World object
 * @author @scawful
 * 
 * @param playerRef 
 * @param textureRef 
 */
World::World( Player *playerRef, std::map<std::string, sf::Texture> &textureRef ) 
{
    this->textures = textureRef;
    this->player = playerRef;
}

/**
 * @brief Destroy the World:: World object
 * @author @scawful
 * 
 */
World::~World()
{

}

/**
 * @brief Cumulative update routine for any World
 * @author @scawful
 * 
 * @param dt 
 */
void World::update(const float& dt) 
{
    
}