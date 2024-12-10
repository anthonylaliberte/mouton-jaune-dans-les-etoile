// SVP indiquer votre nom prenom et IDUL
// BELOUCIF AHMED RAFIK - 537036872
// Anthony Laliberté - 537029645

#include <string>
#include <vector>
#include "MemorySegment.h"
#include "Program.h"

//constructeur
Program::Program(const std::string &name, size_t memorySize, const std::vector<std::string> &instructions):
    name(name), memorySize(memorySize), instructions(instructions), loaded(false), startAddress(0),
    instructionsSegment(0, 0, MemorySegment::READ_ONLY),
    dataSegment(0, 0, MemorySegment::READ_WRITE) {}

//Methode pour définir le debut d'adresse
void Program::setStartAddress(size_t startAddress){
    this->startAddress = startAddress;
    const size_t instructionSegmentSize = memorySize / 5;
    const size_t dataSegmentSize = memorySize * 4 / 5;
    instructionsSegment = MemorySegment(startAddress, instructionSegmentSize, MemorySegment::READ_ONLY);
    dataSegment = MemorySegment(startAddress + dataSegmentSize, dataSegmentSize, MemorySegment::READ_WRITE);
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

const std::string& Program::getName(){
    return name;
}

bool Program::isLoaded() const{
    return loaded;
}

void Program::setLoaded(bool state){
    loaded = state;
}
