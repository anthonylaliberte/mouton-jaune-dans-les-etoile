//
// Created by Hamza Alaoui on 2024-11-15.
//
// SVP indiquer votre nom prenom et IDUL
// BELOUCIF AHMED RAFIK - 537036872
// Anthony Laliberté - 537029645

#ifndef TP3_CODE_MEMORYMANAGER_H
#define TP3_CODE_MEMORYMANAGER_H
#include <unordered_map>
#include <iostream>
#include <queue>
#include "Program.h"

class MemoryManager {
public:
    MemoryManager();

    //Constructeur adequat
    MemoryManager(size_t ramSize, size_t virtualMemorySize);

    //Methode pour charger le programme
    bool loadProgram(Program &program);

    //Methode pour swapperOut le programme
    void swapOutProgram();

    //Methode pour tester l'access en Memoire
    void testMemoryAccess(Program &program, size_t address, bool writeOperation);

    //Methode pour afficher l'état de la RAM et memoire virtuelle
    void displayMemoryState() const;

    //Methode pour unloader tous les programmes
    void unloadAllPrograms();

private:
    size_t ramSize;
    size_t virtualMemorySize;
    size_t currentRamAddress;
    std::unordered_map<std::string, Program> ram;
    std::unordered_map<std::string, Program> virtualMemory;
    std::queue<std::string> ramQueue;
};
#endif //TP3_CODE_MEMORYMANAGER_H
