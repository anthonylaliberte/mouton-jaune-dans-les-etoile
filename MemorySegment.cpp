// SVP indiquer votre nom prenom et IDUL
// BELOUCIF AHMED RAFIK - 537036872
// Anthony Laliberté - 537029645

#include <vector>
#include <stdexcept>
#include "MemorySegment.h"

//Constructeur
MemorySegment::MemorySegment(size_t startAddress, size_t size, AccessType accessType) :
    startAddress(startAddress), size(size), accessType(accessType), memory(size, 0) {}

//Methode pour tester le type d'access
bool MemorySegment::canAccess(size_t address, AccessType requestType) const{
    bool addressIsInMemorySegment = address >= startAddress && address < startAddress + size;
    bool requestIsAllowed = (requestType == READ_ONLY || accessType == READ_WRITE);
    return addressIsInMemorySegment && requestIsAllowed;
}

//Methode pour lire un char dans une adresse
char MemorySegment::read(size_t address) const{
    if (!canAccess(address, READ_ONLY)) throw std::runtime_error("Access violation: cannot read");
    return memory.at(address - startAddress);
}
//Methode pour ecrire la valeur un char dans une adresse
void MemorySegment::write(size_t address, char value){
    if (!canAccess(address, READ_WRITE)) throw std::runtime_error("Access violation: cannot write");
    memory.at(address - startAddress) = value;
}

//Methode getter avoir le debut d'adresse du segment
size_t MemorySegment::getStartAddress() const{
    return startAddress;
}

//Methode pour avoir l'adresse de fin du segment
size_t MemorySegment::getEndAddress() const{
    return startAddress + size;
}

