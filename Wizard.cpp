#include "Wizard.h" 
void Wizard::styleWizard() const{
    std::cout << "                   ____" << std::endl;
    std::cout << "                  .'* *.'" << std::endl;
    std::cout << "               __/_*_*(_" << std::endl;
    std::cout << "              / _______ \\" << std::endl;
    std::cout << "             _\\_)/___\\(_/_" << std::endl;
    std::cout << "            / _((\\- -/))_ \\" << std::endl;
    std::cout << "            \\ \\())(-)(()/ /" << std::endl;
    std::cout << "             ' \\(((()))/ '" << std::endl;
    std::cout << "            / ' \\)).))/ ' \\" << std::endl;
    std::cout << "           / _ \\ - | - /_  \\" << std::endl;
    std::cout << "          (   ( .;''';. .'  )" << std::endl;
    std::cout << "          _\\\"__ /    )\\ __\"/_" << std::endl;
    std::cout << "            \\/  \\   ' /  \\/" << std::endl;
    std::cout << "             .'  '...' ' )" << std::endl;
    std::cout << "              / /  |  \\ \\" << std::endl;
    std::cout << "             / .   .   . \\" << std::endl;
    std::cout << "            /   .     .   \\" << std::endl;
    std::cout << "           /   /   |   \\   \\" << std::endl;
    std::cout << "         .'   /    b    '.  '." << std::endl;
    std::cout << "     _.-'    /     Bb     '-. '-." << std::endl;
    std::cout << " _.-'       |      BBb       '-.  '-." << std::endl;
    std::cout << "(________mrf\\____.dBBBb.________)____)" << std::endl;

}

Wizard::Wizard() :
    strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0), charisma(0), health(50),
    defaultDashAmount(15), dashAmount(defaultDashAmount), dashUsed(0), potions(2), damage(0), defaultActions(1), actions(defaultActions),
    alive(true), missChance(0), spellPoints(3), teleportDistance(50), stunned(false), distance(50) { 
    setStats(); 
}
Wizard::Wizard(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) :
    strength(strength), dexterity(dexterity), constitution(constitution), intelligence(intelligence), wisdom(wisdom), charisma(charisma), health(50),
    defaultDashAmount(15), dashAmount(defaultDashAmount), dashUsed(0), potions(2), damage(0), defaultActions(1), actions(defaultActions),
    alive(true), missChance(0), spellPoints(3), teleportDistance(50), stunned(false), distance(50) { 
    setStats(); 
}

void Wizard::setStats(){
    //set health, armor, potions, actions, dash amount, and amount of spells
    if(constitution ==  20){
        health = 100;
    } else if (constitution == 1){
        health = 20;
    } else if (constitution > 15 && constitution < 20){
        health = 75;
    } else if (constitution > 11 && constitution < 16){
        health = 60;
    }

    if (intelligence == 20){
        actions = 3;
        teleportDistance = 100;
    } else if (intelligence >= 15 && intelligence <= 19){
        actions = 2;
        teleportDistance = 70;
    } else if (intelligence >= 10 && intelligence <= 14){
        teleportDistance = 60;
    } else if (intelligence >= 2 && intelligence <= 5){
        teleportDistance = 40;
    } else if (intelligence == 1){
        teleportDistance = 30;
    }

    if (charisma == 20){
        potions = 4;
    } else if (charisma > 16 && charisma < 20){
        potions = 3;
    }

    if(wisdom == 20){
        defaultDashAmount = 30;
    } else if (wisdom > 16 && wisdom < 20){
        defaultDashAmount = 25;
    } else if (wisdom > 10 && wisdom < 17){
        defaultDashAmount = 20;
    }

}
void Wizard::checkStun(bool _stunned){
    stunned = _stunned;
}
void Wizard::characterTurn(Character* opponent){
    actions = defaultActions;
    dashAmount = defaultDashAmount;
    if (stunned){
        actions = 0;
        cout << "*Your Dazed.*\n";
    }
    bool turn = true;
    while(turn){
        characterMenu();
        int choice;
        cin >> choice;
        while (choice <= 0 && choice >= 8) {
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
        if (spellPoints == 0){
            cout << "*You've Run Out of Spells!*\n";
        } else {
            useTeleport(opponent);
        }
            break;
        case 5:
            usePotion();
            break;
        case 6:
            useDash(opponent);
            break;
        case 7:
            turn = false;
            stunned = false;
            break;
        default:
            break;
        }
    }
}

void Wizard::characterMenu() const{
    cout << "\nHealth: " << health << "\n";
    cout << "Action: " << actions << "\n\n";
    cout << "Opponent distance: " << distance << "m\n\n";
    cout << "Options:\n";

    if (actions != 0) {
        cout << "Attack:\n";
        cout << "1. Cantrip\n\n";

        if (spellPoints != 0) {
            cout << "Spells: " << spellPoints << " left\n";
            cout << "2. Disintegrate\n";
            cout << "3. ThunderBolt\n";
            cout << "4. Teleport\n\n";
        }

        cout << "5. Potion: " << potions << " potions\n";
    }

    if (dashAmount != 0 && !stunned) {
        cout << "6. Dash: " << dashAmount << "m\n";
    }

    cout << "7. End Turn\n\n";
    styleWizard();
    cout << "\n\n";
}

void Wizard::useAttack(Character* opponent, int choice){
    if (actions == 0){
        cout << "*No actions left*\n\n";
        return;
    } else {
        actions--;
        setDamage(choice);
    }
    opponent->receiveDamage(damage);
    cout << "*You Did " << damage << " Damage!*\n";
}

void Wizard::setDamage(int choice){
    switch (choice) {
    case 1:
        if (distance > 60){
            cout << "*Your Magic Can't Reach.*\n";
        } else {
            useCantrip();
        }
        break;
    case 2:
        if (spellPoints == 0){
            cout << "*You've Run Out of Spells!*\n";
        } else if (distance > 60) {
            cout << "*Your Magic Can't Reach.*\n";
        } else {
            useDisintegrate();
        }
        break;
    case 3:
        if (spellPoints == 0){
            cout << "*You've Run Out of Spells!*\n";
        } else if (distance > 60) {
            cout << "*Your Magic Can't Reach.*\n";
        } else {
            useThunderbolt();
        }
        break;
    default:
        break;
    }
}

void Wizard::useCantrip(){
    damage = 15;
    if (intelligence == 20){
        damage += rand() % 21;
    } else if (intelligence >= 16 && intelligence <= 19){
        damage += rand() % 11;
    } else if (intelligence >= 11 && intelligence <= 15){
        damage += rand() % 6;
    } else if (intelligence >= 3 && intelligence <= 2){
        damage -= rand() % 6;
    } else if (intelligence == 1){
        damage -= rand() % 11;
    }

    missChance = (rand() % 20) + 1;
    if (intelligence == 20 && missChance <= 2) {
        damage = 0;
        cout << "*You Scorched The Ground!*\n";
    } else if (intelligence >= 16 && intelligence <= 19 && missChance <= 6) {
        damage = 0;
        cout << "*You Scorched The Ground!*\n";
    } else if (intelligence >= 11 && intelligence <= 15 && missChance <= 8) {
        damage = 0;
        cout << "*You Scorched The Ground!*\n";
    } else if (intelligence >= 4 && intelligence <= 10 && missChance <= 10) {
        damage = 0;
        cout << "*You Scorched The Ground!*\n";
    } else if (intelligence >= 3 && intelligence <= 2 && missChance <= 14) {
        damage = 0;
        cout << "*You Scorched The Ground!*\n";
    } else if (intelligence == 1 && missChance <= 16) {
        damage = 0;
        cout << "*You Scorched The Ground!*\n";
    }
}
void Wizard::useDisintegrate(){
    spellPoints--;
    damage = 100;
    if (intelligence == 20){
        damage += rand() % 51; 
    } else if (intelligence >= 16 && intelligence <= 19){
        damage += rand() % 21;
    } else if (intelligence >= 11 && intelligence <= 15){
        damage += rand() % 11;
    }else if (intelligence >= 3 && intelligence <= 2){
        damage -= rand() % 11;
    } else if (intelligence == 1){
        damage -= rand() % 26;
    }

    missChance = (rand() % 20) + 1;
    if (intelligence == 20 && missChance <= 15) {
        damage = 0;
        cout << "*A Leaf Was Decimated!*\n";
    } else if (intelligence >= 16 && intelligence <= 19 && missChance <= 16) {
        damage = 0;
        cout << "*A Leaf Was Decimated!*\n";
    } else if (intelligence >= 11 && intelligence <= 15 && missChance <= 17) {
        damage = 0;
        cout << "*A Leaf Was Decimated!*\n";
    } else if (intelligence >= 4 && intelligence <= 10 && missChance <= 18) {
        damage = 0;
        cout << "*A Leaf Was Decimated!*\n";
    } else if (intelligence >= 3 && intelligence <= 2 && missChance <= 19) {
        damage = 0;
        cout << "*A Leaf Was Decimated!*\n";
    } else if (intelligence == 1 && missChance <= 20) {
        damage = 0;
        cout << "*A Leaf Was Decimated!*\n";
    }
}
void Wizard::useThunderbolt(){
    spellPoints--;
    damage = 45;
    if (intelligence == 20){
        damage += rand() % 31; 
    } else if (intelligence >= 16 && intelligence <= 19){
        damage += rand() % 16;
    } else if (intelligence >= 11 && intelligence <= 15){
        damage += rand() % 6;
    }else if (intelligence >= 3 && intelligence <= 2){
        damage -= rand() % 16;
    } else if (intelligence == 1){
        damage -= rand() % 26;
    }

        missChance = (rand() % 20) + 1;
    if (intelligence == 20 && (missChance <= 1 || missChance <= 12)) {
        damage = 0;
        cout << "*You Ran Out of Charge!*\n";
    } else if (intelligence >= 16 && intelligence <= 19 && missChance <= 5) {
        damage = 0;
        cout << "*You Ran Out of Charge!*\n";
    } else if (intelligence >= 11 && intelligence <= 15 && missChance <= 6) {
        damage = 0;
        cout << "*You Ran Out of Charge!*\n";
    } else if (intelligence >= 4 && intelligence <= 10 && missChance <= 7) {
        damage = 0;
        cout << "*You Ran Out of Charge!*\n";
    } else if (intelligence >= 3 && intelligence <= 2 && missChance <= 8) {
        damage = 0;
        cout << "*You Ran Out of Charge!*\n";
    } else if (intelligence == 1 && missChance <= 10) {
        damage = 0;
        cout << "*You Ran Out of Charge!*\n";
    }
}
void Wizard::useTeleport(Character* opponent) {
    spellPoints--;
    int teleport;
    cout << "You Can Teleport Up Too " << teleportDistance << "m\n";
    cout << "Enter a Distance: ";
    while (!(cin >> teleport) || abs(teleport) > teleportDistance) {
        cout << "Enter a valid distance: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    distance += dashUsed;
    opponent->updateDistance(dashUsed);
    cout << "\n\n";
}
void Wizard::useDash(Character* opponent){
    if (dashAmount == 0 || stunned) {
        cout << "*Can't Move*\n";
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
void Wizard::updateDistance(int Distance){
    distance += Distance;
}
void Wizard::usePotion(){
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

void Wizard::receiveDamage(int damage) {
    health -= damage;
    if (health < 0){
        health = 0;
        alive = false;
    }
}
bool Wizard::isAlive() const{
    return alive;
}
int Wizard::getDashUsed() const{
    return dashUsed;
}
Wizard::~Wizard(){}