#include "Overworld.hpp"

void Overworld::initTextures() {
    
}

void Overworld::initEnemies() {
    
}

Overworld::Overworld() {
    cout << "Overworld created" << endl;
}

Overworld::~Overworld() {
    cout << "Overworld destroyed" << endl;
}

void Overworld::update(const float& dt) {
    
}

void Overworld::render(sf::RenderTarget &target) 
{
    // sets background to white for regions without objects being rendered over them
    target.clear( sf::Color::Red );
}
