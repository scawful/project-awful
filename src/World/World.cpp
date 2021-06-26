#include "World.hpp"

void World::initTextures() 
{
    
}

World::World( Player *playerRef, std::map<std::string, sf::Texture> &textureRef ) 
{
    this->textures = textureRef;
    this->player = playerRef;
}

World::~World()
{

}

void World::update(const float& dt) 
{
    
}