// SVP indiquer votre nom prenom et IDUL
// BELOUCIF AHMED RAFIK - 537036872
// Anthony Laliberté - 537029645

#include <string>
#include "Program.h"
#include "MemoryManager.h"

// === Fonction principale ===
int main() {
    //Important pour les operations d'affichage svp afficher l'adresse de depart pour chacun des programmes ainsi que sa taille
    //Example :
    //--- État de la RAM ---
    //Programme : Program4 | Adresse de départ : 1048576 | Taille : 2097152 octets
    //Programme : Program1 | Adresse de départ : 0 | Taille : 1048576 octets

    // Initialiser le memoryManager avec RAM: 4 MB, Virtual Memory: 10 MB
    // Créer quatre programme 1 (1MB),2 (2MB),3 (1MB),4 (2 MB) et loader les un par un (en gardant l'ordre 1 2 3 4) et en affichant l'état de la RAM et memoire virtuelle apres chaque programme loader
    // Vider ensuite la memoire
    // Créer program 5 (1MB) et 6 (2MB)
    // Loader et charger les deux en memoire
    // --Verification et affichage
    // Verifier l'access en lecture et ensuite en ecriture sur le segment d'inscructions pour program5
    // Verifier l'access en lecture et ensuite en ecriture sur le segment de données pour program5
    // Verifier l'access en lecture et ensuite en ecriture sur le segment d'inscructions pour program6
    // Verifier l'access en lecture et ensuite en ecriture sur le segment de données pour program6

    // Initialisation

    const size_t SIZE_OF_MB = 1024 * 1024;
    const size_t SIZE_OF_PROGRAM_1 = 1 * SIZE_OF_MB,
            SIZE_OF_PROGRAM_2 = 2 * SIZE_OF_MB,
            SIZE_OF_PROGRAM_3 = 1 * SIZE_OF_MB,
            SIZE_OF_PROGRAM_4 = 2 * SIZE_OF_MB,
            SIZE_OF_PROGRAM_5 = 1 * SIZE_OF_MB,
            SIZE_OF_PROGRAM_6 = 2 * SIZE_OF_MB;
    const size_t START_OF_PROGRAM_5_INSTRUCTION = 0,
            START_OF_PROGRAM_5_DATA = START_OF_PROGRAM_5_INSTRUCTION + SIZE_OF_PROGRAM_5 * 4 / 5,
            START_OF_PROGRAM_6_INSTRUCTION = START_OF_PROGRAM_5_INSTRUCTION + SIZE_OF_PROGRAM_5,
            START_OF_PROGRAM_6_DATA = START_OF_PROGRAM_6_INSTRUCTION + + SIZE_OF_PROGRAM_6 * 4 / 5;

    MemoryManager memoryManager(4 * SIZE_OF_MB, 10 * SIZE_OF_MB);

    // Création des programmes
    Program program1("Program1", SIZE_OF_PROGRAM_1, {"Instruction1"});
    Program program2("Program2", SIZE_OF_PROGRAM_2, {"Instruction1"});
    Program program3("Program3", SIZE_OF_PROGRAM_3, {"Instruction1"});
    Program program4("Program4", SIZE_OF_PROGRAM_4, {"Instruction1"});

    // Chargement des programmes 1 à 4
    memoryManager.loadProgram(program1);
    memoryManager.displayMemoryState();
    memoryManager.loadProgram(program2);
    memoryManager.displayMemoryState();
    memoryManager.loadProgram(program3);
    memoryManager.displayMemoryState();
    memoryManager.loadProgram(program4);
    memoryManager.displayMemoryState();

    // Vidage de la mémoire
    memoryManager.unloadAllPrograms();

    // Création des programmes 5 et 6
    Program program5("Program5", SIZE_OF_PROGRAM_5, {"Instruction1"});
    Program program6("Program6", SIZE_OF_PROGRAM_6, {"Instruction1"});

    // Chargement des programmes 5 et 6
    memoryManager.loadProgram(program5);
    memoryManager.displayMemoryState();
    memoryManager.loadProgram(program6);
    memoryManager.displayMemoryState();

    // Valider l'acces memoire pour Program5
    memoryManager.testMemoryAccess(program5, START_OF_PROGRAM_5_INSTRUCTION, false);
    memoryManager.testMemoryAccess(program5, START_OF_PROGRAM_5_INSTRUCTION, true);
    memoryManager.testMemoryAccess(program5, START_OF_PROGRAM_5_DATA, false);
    memoryManager.testMemoryAccess(program5, START_OF_PROGRAM_5_DATA, true);

    // Valider l'acces memoire pour Program6
    memoryManager.testMemoryAccess(program6, START_OF_PROGRAM_6_INSTRUCTION, false);
    memoryManager.testMemoryAccess(program6, START_OF_PROGRAM_6_INSTRUCTION, true);
    memoryManager.testMemoryAccess(program6, START_OF_PROGRAM_6_DATA, false);
    memoryManager.testMemoryAccess(program6, START_OF_PROGRAM_6_DATA, true);

    return 0;
}
