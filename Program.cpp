//
// Created by Hamza Alaoui on 2024-11-15.
//
// SVP indiquer votre nom prenom et IDUL

#include <string>
#include <vector>
#include "MemorySegment.h"
#include "Program.h"

//constructeur
Program::Program(const std::string &name, size_t memorySize, const std::vector<std::string> &instructions):
    name(name), memorySize(memorySize), instructions(instructions), loaded(false), startAddress(0),
    instructionsSegment(0, memorySize / 2, MemorySegment::READ_ONLY),
    dataSegment(memorySize / 2, memorySize / 2, MemorySegment::READ_WRITE) {}

//Methode pour définir le debut d'adresse
void Program::setStartAddress(size_t startAddress){
    this->startAddress = startAddress;
    instructionsSegment = MemorySegment(startAddress, memorySize / 2, MemorySegment::READ_ONLY);
    dataSegment = MemorySegment(startAddress + memorySize / 2, memorySize / 2, MemorySegment::READ_WRITE);
}

//Getters et Setters
const MemorySegment& Program::getInstructionsSegment(){
    return instructionsSegment;
}

MemorySegment& Program::getDataSegment(){
    return dataSegment;
}

size_t Program::getStartAddress() const{
    return startAddress;
}

size_t Program::getMemorySize() const{
    return memorySize;
}

const std::string& Program::getName() const{
    return name;
}

bool Program::isLoaded() const{
    return loaded;
}

void Program::setLoaded(bool state){
    loaded = state;
}
