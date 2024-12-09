//
// Created by Hamza Alaoui on 2024-11-15.
//
// SVP indiquer votre nom prenom et IDUL

#include <unordered_map>
#include <iostream>
#include "MemoryManager.h"
#include "Program.h"


MemoryManager::MemoryManager(){
    std::cout << "MemoryManager" << std::endl;
}

//Constructeur adequat
MemoryManager::MemoryManager(size_t ramSize, size_t virtualMemorySize){

}

//Methode pour charger le programme
bool MemoryManager::loadProgram(Program &program){

}

//Methode pour swapperOut le programme
void MemoryManager::swapOutProgram(){

}

//Methode pour tester l'access en Memoire
void MemoryManager::testMemoryAccess(Program &program, size_t address, bool writeOperation){

}

//Methode pour afficher l'état de la RAM et memoire virtuelle
void MemoryManager::displayMemoryState() const{

}

//Methode pour unloader tous les programmes
void MemoryManager::unloadAllPrograms(){

}
