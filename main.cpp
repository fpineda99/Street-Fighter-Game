// g++ -o main.exe main.cpp character.cpp Barbarian.cpp Wizard.cpp Monk.cpp
// .\main.exe
#include "character.h"
#include "Barbarian.h"
#include "Wizard.h"
#include "Monk.h"
#include <fstream>

void pickWizard(){
    std::cout << "W   W  III  ZZZZZ AAAAA RRRRR  DDDDD\n";
    std::cout << "W   W   I      ZZ A   A R   RR D   DD\n";
    std::cout << "W W W   I     ZZ  AAAAA RRRRR  D   DD\n";
    std::cout << "W W W   I    ZZ   A   A R  RR  D   DD\n";
    std::cout << " W W   III  ZZZZZ A   A R   RR DDDDD\n\n";
}
void pickBarbarian(){
    std::cout << "  BBBBB   AAAAA  RRRRR   BBBBB   AAAAA  RRRRR   III  AAAAA N   N\n";
    std::cout << "  B   BB  A   A  R   RR  B   BB  A   A  R   RR   I   A   A NN  N \n";
    std::cout << "  BBBBB   AAAAA  RRRRR   BBBBB   AAAAA  RRRRR    I   AAAAA N N N \n";
    std::cout << "  B   BB  A   A  R  RR   B   BB  A   A  R  RR    I   A   A N  NN \n";
    std::cout << "  BBBBB   A   A  R   RR  BBBBB   A   A  R   RR  III  A   A N   N \n\n";

}
void pickMonk(){
    std::cout << "M   M  OOO  N   N K   K\n";
    std::cout << "MM MM O   O NN  N K  K \n";
    std::cout << "M M M O   O N N N KK   \n";
    std::cout << "M   M O   O N  NN K  K \n";
    std::cout << "M   M  OOO  N   N K   K\n\n";

}

void displayStats(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) {
    cout << "Strength: " << strength << "              Choose Your Character\n";
    cout << "Dexterity: " << dexterity << "                                 \n";
    cout << "Constitution: " << constitution << "          Barbarian (Press 1)  \n";
    cout << "Intelligence: " << intelligence << "          Wizard (Press 2)\n";
    cout << "Wisdom: " << wisdom << "                Monk (Press 3)\n";
    cout << "Charisma: " << charisma << "\n";
}
void saveCharacter(Character* Winner, int stats[6], const char* filename){
    ofstream file(filename);

    if(file.is_open()){
        string className = typeid(*Winner).name();
        file << className << " " << stats[0] << " " << stats[1] << " " << stats[2] << " " << stats[3] << " " << stats[4] << " " << stats[5] << "\n";

        file.close();
        cout << "Character saved successfully!\n";
    } else {
        cerr << "Unable to open file for saving.\n";
    }
}
Character* loadCharacter(const char* filename){
    ifstream file(filename);

    if(file.is_open()){
        string className;
        int stats[6];
        file >> className >> stats[0] >> stats[1] >> stats[2] >> stats[3] >> stats[4] >> stats[5]; 

        file.close();
        if (className == "Barbarian") {
            return new Barbarian(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
        } else if (className == "Wizard") {
            return new Wizard(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
        } else if (className == "Monk") {
            return new Monk(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
        } else {
            cerr << "Invalid Character Type.\n";
            return nullptr;
        }
    } else {
        cerr << "Unable to open file for loading.\n";
        return nullptr;
    }
}
Character* chooseCharacter(Character* player, int stats[6]) {
    cout << "Do You Have a Character You Want To Use? (Y or N)\n";
    char loadChoice;
    while (!(cin >> loadChoice) || (loadChoice != 'Y' && loadChoice != 'N')) {
        cout << "Invalid Option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (loadChoice == 'Y'){
        cout << "Enter Your File Name: ";
        string fileName;
        cin >> fileName;
        cout << "\n";
        player = loadCharacter(fileName.c_str());
        return player;
    } else {
        displayStats(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);

        int choice;
        cin >> choice;

        while (choice != 1 && choice != 2 && choice != 3) {
            cout << "Invalid Choice\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                pickBarbarian();
                player = new Barbarian(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
                break;
            case 2:
                pickWizard();
                player = new Wizard(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
                break;
            case 3:
                pickMonk();
                player = new Monk(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5]);
                break;
            default:
                break;
        }

        return player;
    }
}
void duel(Character* player1, Character* player2, int stats1[6], int stats2[6]) {
    // Main game loop
    Character* Winner = nullptr;
    int stats[6];
    
    while (player1->isAlive() && player2->isAlive()) {
        // Player 1's turn
        cout << "Player 1's turn:\n";
        player1->characterTurn(player2);

        // Check if Player 2 is defeated
        if (!player2->isAlive()) {
            cout << "Player 2s Been Slain! Player 1 Wins!!!\n";
            Winner = player1;
            // Copy stats individually
            for (int i = 0; i < 6; ++i) {
                stats[i] = stats1[i];
            }
            break;
        }

        // Player 2's turn
        cout << "Player 2's turn:\n";
        player2->characterTurn(player1);

        // Check if Player 1 is defeated
        if (!player1->isAlive()) {
            Winner = player2;
            // Copy stats individually
            for (int i = 0; i < 6; ++i) {
                stats[i] = stats2[i];
            }
            cout << "Player 1s Been Slain! Player 2 Wins!!!\n";
            break;
        }
    }
    
    cout << "Winner! Would You Like To Save Your Character? (Y or N)\n";
    char choice;
    while (!(cin >> choice) || (choice != 'Y' && choice != 'N')) {
        cout << "Invalid Option.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (choice == 'Y') {
        saveCharacter(Winner, stats, "_savedCharacter.txt");
    }
}


int main() {
    srand(time(nullptr));
    const int statSize = 6;
    int stats1[statSize];
    int stats2[statSize];

    for (int i = 0; i < statSize; i++) {
        stats1[i] = (rand() % 20) + 1;
        stats2[i] = (rand() % 20) + 1;
    }

    cout << "Press Any Button to Start!\n";
    cin.get();

    Character* player1 = chooseCharacter(player1, stats1);
    Character* player2 = chooseCharacter(player2, stats2);

    // Start the duel between two players
    duel(player1, player2, stats1, stats2);

    // Clean up memory
    delete player1;
    delete player2;

    return 0;
}
