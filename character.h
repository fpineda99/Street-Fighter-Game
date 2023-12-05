#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <random>

using namespace std;

class Character {
public:

    virtual void characterTurn(Character* opponent) = 0;
    virtual void receiveDamage(int damage) = 0;
    virtual bool isAlive() const = 0;
    virtual void checkStun(bool ifStun) = 0;
    virtual void updateDistance(int Distance) = 0;
    
    virtual ~Character();
};