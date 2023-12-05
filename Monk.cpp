#include "Monk.h"
void Monk::styleMonk() const{
    cout << "           q(-_-)p \n";
    cout << "           '_) (_`\n";
    cout << "          /__/ \\\n";
    cout << "         _(<_   / )_\n";
    cout << "        (__\\_\\_|_/__)\n";
}
Monk::Monk():
    strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0), charisma(0), health(45),
    defaultDashAmount(60), dashAmount(defaultDashAmount), dashUsed(0), potions(2), damage(0), defaultActions(2), actions(defaultActions), distance(50),
    alive(true), missChance(0), stunPoints(2), windUpPunch(0), windUpPoints(2), stunned(false), stun(true){ 
    setStats(); 
}
Monk::Monk(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) :
    strength(strength), dexterity(dexterity), constitution(constitution), intelligence(intelligence), wisdom(wisdom), charisma(charisma), 
    health(45), defaultDashAmount(60), dashAmount(defaultDashAmount), dashUsed(0), potions(2), damage(0), defaultActions(2), actions(defaultActions), distance(50),
    alive(true), missChance(0), stunPoints(1), windUpPunch(0), windUpPoints(2), stunned(false), stun(true){ 
    setStats(); 
}
Monk::~Monk(){}
void Monk::setStats(){
    if(constitution ==  20){
        health = 80;
    } else if (constitution == 1){
        health = 25;
    } else if (constitution >= 15 && constitution <= 19){
        health = 65;
    } else if (constitution >= 10 && constitution <= 14){
        health = 55;
    }

    if (dexterity == 20){
        defaultDashAmount = 100;
    } else if (dexterity >= 17 && dexterity <= 19){
        defaultDashAmount = 80;
    } else if (dexterity >= 12 && dexterity <= 16){
        defaultDashAmount = 70;
    } else if (dexterity >= 2 && dexterity <= 6){
        defaultDashAmount = 40;
    } else if (dexterity == 1){
        defaultDashAmount = 30;
    }

    if (charisma == 20){
        potions = 3;
    } else if (charisma == 1){
        potions = 1;
    }

    if(wisdom == 20){
        actions = 3;
        stunPoints = 3;
        windUpPoints = 3;
    } else if (wisdom >= 14 && wisdom <= 19){
        stunPoints = 2;
    } else if (wisdom == 1){
        actions = 1;
        stunPoints = 1;
        windUpPoints = 1;
    }
}

void Monk::characterMenu() const{
    cout << "\nHealth: " << health << "\n";
    cout << "Action: " << actions << "\n";
    cout << "Opponent distance: " << distance << "m\n\n";
    cout << "Options:\n";

    if (actions != 0) {
        cout << "Attack:\n";
        cout << "1. Multi-Hit\n\n";

        if (stunPoints != 0) {
            cout << "2. Stun: " << stunPoints << "\n";
        }
        if (windUpPoints != 0) {
            cout << "3. Whin up: " << windUpPoints << "\n";
        }
        if (potions != 0){
            cout << "4. Potion: " << potions << "\n";
        }
    }

    if (dashAmount != 0 && !stunned) {
        cout << "5. Dash: " << dashAmount << "m\n";
    }

    cout << "6. End Turn\n\n";
    styleMonk();
    cout << "\n\n";
}
void Monk::checkStun(bool _stunned){
    stunned = _stunned;
}
void Monk::characterTurn(Character* opponent){
    actions = defaultActions;
    dashAmount = defaultDashAmount;
    bool turn = true;
    if (stunned) {
        actions = 0;
        cout << "*You're Dazed.*\n";
    }
    while(turn){
        characterMenu();
        int choice;
        cin >> choice;
        while (choice <= 1 && choice >= 6) {
            cout << "Invalid choice. Enter your choice again: ";
            cin >> choice;
        }
        switch (choice) {
        case 1:
            useAttack(opponent, choice);
            break;
        case 2:
            useAttack(opponent, choice);
            break;
        case 3:
            useAttack(opponent, choice);
            break;
        case 4:
            usePotion();
            break;
        case 5:
            useDash(opponent);
            break;
        case 6:
            turn = false;
            stunned = false;
            break;
        default:
            break;
        }
    }
}

void Monk::missMultiPunch(){
    missChance = (rand() % 20) + 1;
    if (wisdom == 20 && missChance <= 2) {
        damage = 0;
        cout << "*Weaved!* ";
    } else if (wisdom  >= 16 && wisdom  <= 19 && missChance <= 4) {
        damage = 0;
        cout << "*Weaved!* ";
    } else if (wisdom  >= 11 && wisdom  <= 15 && missChance <= 6) {
        damage = 0;
        cout << "*Weaved!* ";
    } else if (wisdom  >= 4 && wisdom  <= 10 && missChance <= 7) {
        damage = 0;
        cout << "*Weaved!* ";
    } else if (wisdom  >= 3 && wisdom  <= 2 && missChance <= 9) {
        damage = 0;
        cout << "*Weaved!* ";
    } else if (wisdom  == 1 && missChance <= 13) {
        damage = 0;
        cout << "*Weaved!* ";
    }
}
void Monk::missWindUp(){
    missChance = (rand() % 20) + 1;
    if (wisdom == 20 && missChance <= 2) {
        damage = 0;
    } else if (wisdom  >= 16 && wisdom  <= 19 && missChance <= 4) {
        damage = 0;
    } else if (wisdom  >= 11 && wisdom  <= 15 && missChance <= 6) {
        damage = 0;
    } else if (wisdom  >= 4 && wisdom  <= 10 && missChance <= 7) {
        damage = 0;
    } else if (wisdom  >= 3 && wisdom  <= 2 && missChance <= 9) {
        damage = 0;
    } else if (wisdom  == 1 && missChance <= 13) {
        damage = 0;
    }
}
void Monk::missStun(){
        missChance = (rand() % 20) + 1;
    if (wisdom == 20 && missChance <= 2) {
        stun = false;
        cout << "*No Bonk.* ";
    } else if (wisdom  >= 16 && wisdom  <= 19 && missChance <= 6) {
        stun = false;
        cout << "*No Bonk.* ";
    } else if (wisdom  >= 11 && wisdom  <= 15 && missChance <= 8) {
        stun = false;
        cout << "*No Bonk.* ";
    } else if (wisdom  >= 4 && wisdom  <= 10 && missChance <= 9) {
        stun = false;
        cout << "*No Bonk.* ";
    } else if (wisdom  >= 3 && wisdom  <= 2 && missChance <= 13) {
        stun = false;
        cout << "*No Bonk.* ";
    } else if (wisdom  == 1 && missChance <= 15) {
        stun = false;
        cout << "*No Bonk.* ";
    }
}
void Monk::useMultiPunch(){
    damage = 5 + (rand() % 8);
    if (strength == 20){
        damage = 8 + (rand() % 13);
    } else if (strength >= 16 && strength <= 19){
        damage = 8 + (rand() % 10);
    } else if (strength >= 12 && strength <= 15){
        damage = 7 + (rand() % 8);
    } else if (strength == 1){
        damage = 3 + (rand() % 7);
    }
}
void Monk::useWindUpPunch(){
    actions--;
    windUpPoints--;
    useMultiPunch();
    missWindUp();
    damage = ceil(damage * 1.6);
}
void Monk::useStun(Character* opponent){
    actions--;
    stunPoints--;
    stun = true;
    missStun();
    opponent->checkStun(stun);
    if (stun){
        cout << "*You Bonked your Opponent!*\n";
    }
}  

void Monk::useAttack(Character* opponent, int choice){
    switch (choice) {
    case 1:
        if (actions == 0){
            cout << "*No Swings Left In You.*\n";
        } else if (distance > 5){
            cout << "*You're too far to hit.*\n";
        } else {
            actions--;
            for (int i = 0; i < 3; i++){
                useMultiPunch();
                missMultiPunch();
                opponent->receiveDamage(damage);
                cout << damage << " Damage!\n";
            }
        }
        break;
    case 2:
        if (stunPoints == 0){
            cout << "*Cant Bonk No More.*\n";
        }  else if (distance > 5){
            cout << "*You're too far to hit.*\n";
        } else {
            useStun(opponent);
        }
        break;
    case 3:
        if (windUpPoints == 0){
            cout << "*Nothing To Wind.*\n";
        }  else if (distance > 5){
            cout << "*You're too far to hit.*\n";
        } else {
            useWindUpPunch();
            opponent->receiveDamage(damage);
            cout << "Winding Up!!!\n3\n2\n1\n";
            cout << "*You Did " << damage << " Damage!*\n";
            if (damage == 0){
                cout << "*The Air Snaps Around You.*\n";
            }
        }
        break;
    default:
        break;
    }
}
void Monk::useDash(Character* opponent){
    if (dashAmount == 0 || stunned) {
        cout << "Can't Move\n";
        return;
    }

    cout << dashAmount << "m of dash left\n";
    cout << "Enter a Distance: ";
    while (!(cin >> dashUsed) || abs(dashUsed) > dashAmount) {
        cout << "Enter a valid distance: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    dashAmount -= abs(dashUsed);
    distance += dashUsed;
    opponent->updateDistance(dashUsed);
}
void Monk::updateDistance(int Distance){
    distance += Distance;
}
void Monk::usePotion(){
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

void Monk::receiveDamage(int damage){
    health -= damage;
    if (health < 0){
        health = 0;
        alive = false;
    }
}
bool Monk::isAlive() const{
    return alive;
}
int Monk::getDashUsed() const{
    return dashUsed;
}