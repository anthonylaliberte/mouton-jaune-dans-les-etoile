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

    const size_t NUMBER_OF_BIT_IN_MB = 1024 * 1024;
    MemoryManager memoryManager(4 * NUMBER_OF_BIT_IN_MB, 10 * NUMBER_OF_BIT_IN_MB);

    // Création des programmes
    Program program1("Program1", 1 * NUMBER_OF_BIT_IN_MB, {"Instruction1"});
    Program program2("Program2", 2 * NUMBER_OF_BIT_IN_MB, {"Instruction1"});
    Program program3("Program3", 1 * NUMBER_OF_BIT_IN_MB, {"Instruction1"});
    Program program4("Program4", 2 * NUMBER_OF_BIT_IN_MB, {"Instruction1"});

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
    Program program5("Program5", 1 * NUMBER_OF_BIT_IN_MB, {"Instruction1"});
    Program program6("Program6", 2 * NUMBER_OF_BIT_IN_MB, {"Instruction1"});

    // Chargement des programmes 5 et 6
    memoryManager.loadProgram(program5);
    memoryManager.displayMemoryState();
    memoryManager.loadProgram(program6);
    memoryManager.displayMemoryState();

    // Accès mémoire pour Program5
    memoryManager.testMemoryAccess(program5, 0, false);       // Lecture instructions
    memoryManager.testMemoryAccess(program5, 524288, true);   // Ecriture données

    // Accès mémoire pour Program6
    memoryManager.testMemoryAccess(program6, 1048576, false); // Lecture instructions
    memoryManager.testMemoryAccess(program6, 2097152, true);  // Ecriture données (adresse corrigée)

    return 0;
}
