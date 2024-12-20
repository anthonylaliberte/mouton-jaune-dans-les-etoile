// SVP indiquer votre nom prenom et IDUL
// BELOUCIF AHMED RAFIK - 537036872
// Anthony Laliberté - 537029645

#include <unordered_map>
#include <iostream>
#include "MemoryManager.h"
#include "Program.h"

MemoryManager::MemoryManager(){}

//Constructeur adequat
MemoryManager::MemoryManager(size_t ramSize, size_t virtualMemorySize):
    ramSize(ramSize), virtualMemorySize(virtualMemorySize), currentRamAddress(0), currentVirtualMemoryUsed(0) {}

//Methode pour charger le programme
bool MemoryManager::loadProgram(Program &program){
    //s'assurer qu'il y a assez de place dans la ram pour le program
    while(currentRamAddress + program.getMemorySize() > ramSize){
        //s'il n'y a pas de assez de place dans la memoire virtuel il n'est pas possible de charger le program
        if(currentVirtualMemoryUsed + program.getMemorySize() > virtualMemorySize){
            return false;
        }
        swapOutProgram();
    }

    //retirer le program de la memoire virtuel s'il y etait deja
    virtualMemory.erase(program.getName());

    //ajouter le program dans la ram
    program.setStartAddress(currentRamAddress);
    program.setLoaded(true);
    currentRamAddress += program.getMemorySize();
    ram.insert({program.getName(), program});
    ramQueue.push(program.getName());

    return true;
}

//Methode pour swapperOut le programme
void MemoryManager::swapOutProgram(){
    //obtenir nom du program a swapper
    const std::string swappedProgramName = ramQueue.front();
    ramQueue.pop();

    //retirer le program de la ram
    Program swappedProgram = ram.at(swappedProgramName);
    ram.erase(swappedProgramName);
    swappedProgram.setLoaded(false);

    //ajouter le program dans la memoire virtuel
    virtualMemory.insert({swappedProgramName, swappedProgram});
    currentVirtualMemoryUsed += swappedProgram.getMemorySize();

    //reorganiser les adresses de program
    currentRamAddress = 0;
    for (auto it = ram.begin(); it != ram.end(); it++){
        Program &program = it->second;
        program.setStartAddress(currentRamAddress);
        currentRamAddress += program.getMemorySize();
    }
}

//Methode pour tester l'access en Memoire
void MemoryManager::testMemoryAccess(Program &program, size_t address, bool writeOperation) {
    // Récupérer les plages des segments
    size_t instrStart = program.getInstructionsSegment().getStartAddress();
    size_t instrEnd = program.getInstructionsSegment().getEndAddress();
    size_t dataStart = program.getDataSegment().getStartAddress();
    size_t dataEnd = program.getDataSegment().getEndAddress();

    try{
        // Vérifier et effectuer l'accès
        if (address >= dataStart && address < dataEnd) {
            // Afficher les plages d'adresses de data pour vérifier
            std::cout << "Data Segment: [" << dataStart << ", " << dataEnd << "]\n";

            //essayer de lire ou d'ecrir en memoire
            if (writeOperation) {
                program.getDataSegment().write(address, 'A');
                std::cout << "Write access successful at address: " << address << "\n";
            } else {
                char value = program.getDataSegment().read(address);
                std::cout << "Read access successful at address: " << address << ", value: " << value << "\n";
            }
        } else if (address >= instrStart && address < instrEnd) {
            // Afficher les plages d'adresses d'instruction pour vérifier
            std::cout << "Instruction Segment: [" << instrStart << ", " << instrEnd << "]\n";

            //essayer de lire ou d'ecrir en memoire
            if (writeOperation) {
                program.getInstructionsSegment().write(address, 'A');
                std::cout << "Write access successful at address: " << address << "\n";
            } else {
                char value = program.getInstructionsSegment().read(address);
                std::cout << "Read access successful at address: " << address << ", value: " << value << "\n";
            }
        } else {
            throw std::runtime_error("Address outside instruction segment");
        }
    } catch (const std::exception &e) {
        std::cout << "Memory access error at address: " << address << " - " << e.what() << "\n";
    }
}

//Methode pour afficher l'état de la RAM et memoire virtuelle
void MemoryManager::displayMemoryState() const{
    std::cout << "--- Etat de la RAM ---\n";
    for (auto it = ram.begin(); it != ram.end(); it++){
        Program program = it->second;
        std::cout << "Programme : " << program.getName()
                  << " | Adresse de depart : " << program.getStartAddress()
                  << " | Taille : " << program.getMemorySize() << " octets\n";
    }
}

//Methode pour unloader tous les programmes
void MemoryManager::unloadAllPrograms(){
    ram.clear();
    virtualMemory.clear();
    currentRamAddress = 0;
}