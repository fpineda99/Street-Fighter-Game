#include "character.h"
#pragma once

class Wizard : public Character {
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

    int spellPoints;
    int teleportDistance;

public:
    Wizard();
    Wizard(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
    virtual ~Wizard();

    void setStats();
    void useDash(Character* opponent);
    int getDashUsed() const;
    void usePotion();

    void styleWizard() const;
    void useCantrip();
    void useDisintegrate();
    void useThunderbolt();
    void useTeleport(Character* opponent);
    void useAttack(Character* opponent, int choice);
    void setDamage(int choice);

    void characterMenu() const;
    bool isAlive() const override;
    void characterTurn(Character* opponent) override;
    void receiveDamage(int damage) override;
    void checkStun(bool ifStun) override;
    void updateDistance(int Distance) override;
};
