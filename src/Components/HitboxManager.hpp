#ifndef HITBOXMANGER_HPP
#define HITBOXMANGER_HPP 1

#include "../core.hpp"
#include "HitboxComponent.hpp"

class HitboxManager {
private:
    std::map<unsigned int, HitboxComponent*> enemyDamageDealingHitboxes;  // Enemy damage dealing hitboxes
    std::map<unsigned int, HitboxComponent*> enemyDamageTakingHitboxes;  // Enemy damage taking hitboxes

    std::map<unsigned int, HitboxComponent*> userDamageTakingHitboxes;  // User's Damage taking hitboxes
    std::map<unsigned int, HitboxComponent*> userDamageDealingHitboxes;  // User's Damage dealing hitboxes
protected:
public:
    HitboxManager();
    ~HitboxManager();

    // Modifiers
    bool addEnemyDamageDealingHitbox(unsigned int ID, HitboxComponent* hitbox);
    bool addUserDamageDealingHitbox(unsigned int ID, HitboxComponent* hitbox);
    bool addEnemyDamageTakingHitbox(unsigned int ID, HitboxComponent* hitbox);
    bool addUserDamageTakingHitbox(unsigned int ID, HitboxComponent* hitbox);

    // Functions
    void update();
};

#endif