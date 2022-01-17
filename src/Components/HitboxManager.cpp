#include "HitboxManager.hpp"

HitboxManager::HitboxManager() {
    return;
}

HitboxManager::~HitboxManager() {
    return;
}

bool HitboxManager::addEnemyDamageDealingHitbox(unsigned int ID, HitboxComponent* hitbox) {
    return this->enemyDamageDealingHitboxes.emplace(ID, hitbox).second;
}

bool HitboxManager::addEnemyDamageTakingHitbox(unsigned int ID, HitboxComponent* hitbox) {
    return this->enemyDamageTakingHitboxes.emplace(ID, hitbox).second;
}

bool HitboxManager::addUserDamageDealingHitbox(unsigned int ID, HitboxComponent* hitbox) {
    return this->userDamageDealingHitboxes.emplace(ID, hitbox).second;
}

bool HitboxManager::addUserDamageTakingHitbox(unsigned int ID, HitboxComponent* hitbox) {
    return this->userDamageDealingHitboxes.emplace(ID, hitbox).second;
}

void HitboxManager::update() {
    return;
}