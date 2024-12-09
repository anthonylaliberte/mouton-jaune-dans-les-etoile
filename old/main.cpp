// SVP indiquer votre nom prenom et IDUL


#include <iostream>
#include "MemoryManager.h"

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

    std::cout << "Hello, World!" << std::endl;
    MemoryManager manager();
    return 0;
}
