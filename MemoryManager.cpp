//
// Created by Hamza Alaoui on 2024-11-15.
//
// SVP indiquer votre nom prenom et IDUL

#include <unordered_map>
#include <iostream>
#include "MemoryManager.h"
#include "Program.h"

/*
MemoryManager::MemoryManager(){
    std::cout << "MemoryManager" << std::endl;
}
*/

//Constructeur adequat
MemoryManager::MemoryManager(size_t ramSize, size_t virtualMemorySize):
    ramSize(ramSize), virtualMemorySize(virtualMemorySize), currentRamAddress(0), ram() {}

//Methode pour charger le programme
bool MemoryManager::loadProgram(Program &program){
    if (currentRamAddress + program.getMemorySize() <= ramSize) {
        program.setStartAddress(currentRamAddress);
        program.setLoaded(true);
        ram[program.getName()] = program;
        currentRamAddress += program.getMemorySize();
        return true;
    } else {
        virtualMemory[program.getName()] = program;
        return false;
    }
}

//Methode pour swapperOut le programme
void MemoryManager::swapOutProgram(){

}

//Methode pour tester l'access en Memoire
void MemoryManager::testMemoryAccess(Program &program, size_t address, bool writeOperation) {
    try {
        // Récupérer les plages des segments
        size_t instrStart = program.getInstructionsSegment().getStartAddress();
        size_t instrEnd = program.getInstructionsSegment().getEndAddress();
        size_t dataStart = program.getDataSegment().getStartAddress();
        size_t dataEnd = program.getDataSegment().getEndAddress();

        // Afficher les plages d'adresses pour vérifier
        std::cout << "Instruction Segment: [" << instrStart << ", " << instrEnd << "]\n";
        std::cout << "Data Segment: [" << dataStart << ", " << dataEnd << "]\n";

        // Vérifier et effectuer l'accès
        if (writeOperation) { // Ecriture
            if (address >= dataStart && address < dataEnd) {
                program.getDataSegment().write(address, 'A');
                std::cout << "Write access successful at address: " << address << "\n";
            } else {
                throw std::runtime_error("Access violation: Address outside data segment");
            }
        } else { // Lecture
            if (address >= instrStart && address < instrEnd) {
                char value = program.getInstructionsSegment().read(address);
                std::cout << "Read access successful at address: " << address << ", value: " << value << "\n";
            } else {
                throw std::runtime_error("Access violation: Address outside instruction segment");
            }
        }
    } catch (const std::exception &e) {
        std::cout << "Memory access error at address: " << address << " - " << e.what() << "\n";
    }
}

//Methode pour afficher l'état de la RAM et memoire virtuelle
void MemoryManager::displayMemoryState() const{
    std::cout << "--- Etat de la RAM ---\n";
    for (const auto &entry : ram) {
        const auto &program = entry.second;
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
