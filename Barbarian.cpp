#include "Barbarian.h"

void Barbarian::styleBarbarian() const{
    cout << "               /\\_[]_/\\ " << endl;
    cout << "              |] _||_ [| " << endl;
    cout << "       ___     \\/ || \\/ " << endl;
    cout << "      /___\\       || " << endl;
    cout << "     (|0 0|)      || " << endl;
    cout << "   __/{\\U/}\\_ ___/vvv " << endl;
    cout << "  / \\  {~}   / _|_P| " << endl;
    cout << "  | /\\  ~   /_/   [] " << endl;
    cout << "  |_| (____)        " << endl;
    cout << "  \\_]/______\\         " << endl;
    cout << "     _\\_||_/_           " << endl;
    cout << "    (_,_||_,_) " << endl;

}
Barbarian::Barbarian() : 
    strength(0), dexterity(0), constitution(0), wisdom(0), intelligence(0), charisma(0), health(65),
    ragePoints(1), defaultDashAmount(30), dashAmount(defaultDashAmount), dashUsed(0), potions(0), damage(0), baseDamage(7 + (rand() % 8)), distance(50),
    defaultActions(2), missChance(0), actions(defaultActions), rageActive(false), alive(true), stunned(false) 
{
    setStats();
}
Barbarian::Barbarian(int strength, int dexterity, int constitution, int intelligence , int wisdom, int charisma) : 
    strength(strength), dexterity(dexterity), constitution(constitution), intelligence(intelligence), wisdom(wisdom), charisma(charisma), 
    health(65), ragePoints(1), defaultDashAmount(30), dashAmount(defaultDashAmount), dashUsed(0), potions(0), damage(0), missChance(0), distance(50), 
    baseDamage(7 + (rand() % 8)), defaultActions(2), actions(defaultActions), rageActive(false), alive(true), stunned(false)
{
    setStats();
}

void Barbarian::setStats(){
    if (constitution == 20){
        health = 100;
    } else if (constitution >= 16 && constitution <= 19){
        health = 80;
    } else if (constitution >= 15 && constitution <= 11){
        health = 70;
    } else if (constitution == 1){
        health = 35;
    }

    if (strength == 20){
        ragePoints = 2;
        defaultActions += 1;
    }  else if (strength == 1){
        ragePoints = 0;
        defaultActions -= 1;
    }

    if (charisma == 20){
        potions = 1;
    }

    if (dexterity == 20){
        defaultDashAmount = 45;
    } else if (dexterity == 1){
        defaultDashAmount = 10;
    }
}
void Barbarian::checkStun(bool _stunned){
    stunned = _stunned;
}

void Barbarian::characterTurn(Character* opponent) {
    actions = defaultActions;
    dashAmount = defaultDashAmount;
    bool turn = true;
    if (stunned){
        actions = 0;
        cout << "*Your Dazed.*\n";
    }
    while(turn){
        characterMenu();
        int choice;
        cin >> choice;
        while (choice <= 1 && choice >= 5) {
            cout << "Invalid choice. Enter your choice again: ";
            cin >> choice;
        }
        switch (choice) {
        case 1:
            useAttack(opponent);
            break;
        case 2:
            useRage();
            break;
        case 3:
            usePotion();
            break;
        case 4:
            useDash(opponent);
            break;
        case 5:
            turn = false;
            break;
        default:
            cout << "turn switch\n";
            break;
        }
    }
}

void Barbarian::characterMenu() const {
    cout << "Health: " << health << "\n";
    cout << "Actions: " << actions << "\n";
    cout << "Opponent distance: " << distance << "m\n\n";
    if (rageActive) {
        cout << "*Rage Active!*\n";
    }
    cout << "\nOptions:\n";

    if (actions != 0) {
        cout << "1. Attack\n";
    }
    if (actions != 0 && ragePoints != 0) {
        cout << "2. Rage: " << ragePoints << " rages\n";
    }
    if (actions != 0 && potions != 0) {
        cout << "3. Potion: " << potions << " potions\n";
    }
    if (dashAmount != 0 && !stunned) {
        cout << "4. Dash: " << dashAmount << "m\n";
    }
    cout << "5. End Turn\n";
    styleBarbarian();
    cout << "\n\n";
}

void Barbarian::setDamage(){
    if (strength == 20){
        baseDamage = 10 + (rand() % 26);
    } else if (strength >= 16 && strength <= 19){
        baseDamage = 10 + (rand() % 15);
    } else if (strength >= 12 && strength <= 15){
        baseDamage = 7 + (rand() % 12);
    } else if (strength == 1){
        baseDamage = 0 + (rand() % 8);
    }

    missChance = (rand() % 20) + 1;
    if (dexterity == 20 && missChance <= 2) {
        baseDamage = 0;
    } else if (dexterity >= 16 && dexterity <= 19 && missChance <= 4) {
        baseDamage = 0;
    } else if (dexterity >= 11 && dexterity <= 15 && missChance <= 5) {
        baseDamage = 0;
    } else if (dexterity >= 4 && dexterity <= 10 && missChance <= 8) {
        baseDamage = 0;
    } else if (dexterity >= 2 && dexterity <= 3 && missChance <= 11) {
        baseDamage = 0;
    } else if (dexterity == 1 && missChance <= 15) {
        baseDamage = 0;
    }

    rageDamage = ceil(baseDamage * 1.45);
}

void Barbarian::useAttack(Character* opponent){
    if (actions == 0){
        cout << "*No actions left*\n\n";
        return;
    } else if (distance > 7){
        cout << "*You're too far to hit.*\n\n";
    } else {
        actions--;
        setDamage();
        if (rageActive){
            damage = rageDamage;
            rageActive = false;
        } else {
            damage = baseDamage;
        }
        opponent->receiveDamage(damage);
        if (damage == 0){
            cout << "*Your Swing Missed!*\n";
        } else {
            cout << "*You Did " << damage << " Damage!*\n";
        }
    }
}

void Barbarian::useRage(){
    if (actions == 0){
        cout << "No more actions left\n\n";
    } else if (ragePoints == 0){
        cout << "No more rages\n\n";
    } else {
        actions--;
        ragePoints--;
        rageActive = true;
    }
    return;
}

void Barbarian::useDash(Character* opponent) {
    if (dashAmount == 0 || stunned) {
        cout << "*Can't Move*\n";
        return;
    }

    cout << dashAmount << "m of dash left\n";
    cout << "Enter a Distance: ";
    while (!(cin >> dashUsed) ||  abs(dashUsed) > dashAmount) {
        cout << "Enter a valid distance: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    dashAmount -= abs(dashUsed);
    distance += dashUsed;
    opponent->updateDistance(dashUsed);
}
void Barbarian::updateDistance(int Distance){
    distance += Distance;
}
void Barbarian::usePotion(){
    if (actions == 0){
        cout << "*No more actions left*\n";
    } else if (potions == 0) {
        cout << "*No potions left*\n";
    } else {
        actions -= 1;
        potions -= 1;
        health += 13 + (rand() % 14);
    }
    return;
}

void Barbarian::receiveDamage(int damage){
    health -= damage;
    if (health < 0){
        health = 0;
        alive = false;
    }
}

bool Barbarian::isAlive() const {
    return alive;
}
int Barbarian::getDashUsed() const{
    return dashUsed;
}
Barbarian::~Barbarian(){}