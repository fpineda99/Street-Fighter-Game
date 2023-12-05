#include "character.h"
#pragma once

class Monk : public Character {
private:
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int health;
    int actions;
    int defaultActions;
    int defaultDashAmount;
    int dashAmount;
    int dashUsed;
    int potions;
    int missChance;
    int damage;
    int distance;
    bool alive;
    bool stunned;
    bool stun;

    int stunPoints;
    int windUpPoints;
    int windUpPunch;


public:
    Monk();
    Monk(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
    virtual ~Monk();

    void setStats();
    void useDash(Character* opponent);
    int getDashUsed() const;
    void usePotion();

    void styleMonk() const;
    int useAttack();
    void useAttack(Character* opponent, int choice);
    void setDamage();
    
    void useMultiPunch();
    void useWindUpPunch();
    void useStun(Character* opponent);
    void missMultiPunch();
    void missWindUp();
    void missStun();

    void characterMenu() const;
    bool isAlive() const override;
    void characterTurn(Character* opponent) override;
    void receiveDamage(int damage) override;
    void checkStun(bool ifStun) override;
    void updateDistance(int Distance) override;
};
 