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
    ramSize(ramSize), virtualMemorySize(virtualMemorySize), currentRamAddress(0), ram() {}

//Methode pour charger le programme
bool MemoryManager::loadProgram(Program &program){
    //s'assurer qu'il y a assez de place dans la ram pour le program
    while(currentRamAddress + program.getMemorySize() > ramSize){
        swapOutProgram();
    }

    //retirer le program de la memoire virtuel s'il y etait deja
    virtualMemory.erase(program.getName());

    //ajouter le program dans la ram
    ram.insert({program.getName(), program});
    ramQueue.push(program.getName());
    program.setStartAddress(currentRamAddress);
    program.setLoaded(true);
    currentRamAddress += program.getMemorySize();
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

    //to do reorganiser les adresses de program
    currentRamAddress = 0;
    for (auto it = ram.begin(); it != ram.end(); it++){
        it->second.setStartAddress(currentRamAddress);
        currentRamAddress += it->second.getMemorySize();
    }
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