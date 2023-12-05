#include "character.h"
#pragma once

class Barbarian : public Character {
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

    int ragePoints;
    int baseDamage;
    int rageDamage;
    bool rageActive;

public:
    Barbarian();
    Barbarian(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
    ~Barbarian() override;

    void setStats();
    void setDamage();
    void useAttack(Character* opponent);
    void useRage();
    void useDash(Character* opponent);
    int getDashUsed() const;
    void usePotion();
    void styleBarbarian() const;

    void characterMenu() const;
    bool isAlive() const override;
    void characterTurn(Character* opponent) override;
    void receiveDamage(int damage) override;
    void checkStun(bool ifStun) override;
    void updateDistance(int Distance) override;

};