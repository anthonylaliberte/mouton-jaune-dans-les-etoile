#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// === Déclaration et implémentation de MemorySegment ===
class MemorySegment {
public:
    enum AccessType { READ_ONLY, READ_WRITE };

    MemorySegment(size_t startAddress, size_t size, AccessType accessType)
        : startAddress(startAddress), size(size), accessType(accessType), memory(size, 0) {}

    bool canAccess(size_t address, AccessType requestType) const {
        return address >= startAddress && address < startAddress + size &&
               (requestType == READ_ONLY || accessType == READ_WRITE);
    }

    char read(size_t address) const {
        if (!canAccess(address, READ_ONLY)) throw std::runtime_error("Access violation");
        return memory[address - startAddress];
    }

    void write(size_t address, char value) {
        if (!canAccess(address, READ_WRITE)) throw std::runtime_error("Access violation");
        memory[address - startAddress] = value;
    }

    size_t getStartAddress() const { return startAddress; }
    size_t getEndAddress() const { return startAddress + size; }

private:
    size_t startAddress;
    size_t size;
    AccessType accessType;
    std::vector<char> memory;
};

// === Déclaration et implémentation de Program ===
class Program {
public:
    Program() : name(""), memorySize(0), loaded(false), startAddress(0),
        instructionsSegment(0, 0, MemorySegment::READ_ONLY),
        dataSegment(0, 0, MemorySegment::READ_WRITE) {}

    Program(const std::string &name, size_t memorySize, const std::vector<std::string> &instructions)
        : name(name), memorySize(memorySize), instructions(instructions), loaded(false), startAddress(0),
          instructionsSegment(0, memorySize / 2, MemorySegment::READ_ONLY),
          dataSegment(memorySize / 2, memorySize / 2, MemorySegment::READ_WRITE) {}

    void setStartAddress(size_t startAddress) {
        this->startAddress = startAddress;
        instructionsSegment = MemorySegment(startAddress, memorySize / 2, MemorySegment::READ_ONLY);
        dataSegment = MemorySegment(startAddress + memorySize / 2, memorySize / 2, MemorySegment::READ_WRITE);
    }

    const MemorySegment& getInstructionsSegment() const { return instructionsSegment; }
    MemorySegment& getDataSegment() { return dataSegment; }
    size_t getStartAddress() const { return startAddress; }
    size_t getMemorySize() const { return memorySize; }
    const std::string& getName() const { return name; }
    bool isLoaded() const { return loaded; }
    void setLoaded(bool state) { loaded = state; }

private:
    std::string name;
    size_t memorySize;
    bool loaded;
    size_t startAddress;
    std::vector<std::string> instructions;
    MemorySegment instructionsSegment;
    MemorySegment dataSegment;
};

// === Déclaration et implémentation de MemoryManager ===
class MemoryManager {
public:
    MemoryManager(size_t ramSize, size_t virtualMemorySize)
        : ramSize(ramSize), virtualMemorySize(virtualMemorySize), currentRamAddress(0) {}

    bool loadProgram(Program &program) {
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

    void unloadAllPrograms() {
        ram.clear();
        virtualMemory.clear();
        currentRamAddress = 0;
    }

    void testMemoryAccess(Program &program, size_t address, bool writeOperation) {
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

    void displayMemoryState() const {
        std::cout << "--- Etat de la RAM ---\n";
        for (const auto &entry : ram) {
            const auto &program = entry.second;
            std::cout << "Programme : " << program.getName()
                      << " | Adresse de depart : " << program.getStartAddress()
                      << " | Taille : " << program.getMemorySize() << " octets\n";
        }
    }

private:
    size_t ramSize;
    size_t virtualMemorySize;
    size_t currentRamAddress;
    std::unordered_map<std::string, Program> ram;
    std::unordered_map<std::string, Program> virtualMemory;
};

// === Fonction principale ===
int main() {
    // Important : Initialisation
    MemoryManager memoryManager(4 * 1024 * 1024, 10 * 1024 * 1024);

    // Création des programmes
    Program program1("Program1", 1 * 1024 * 1024, {"Instruction1"});
    Program program2("Program2", 2 * 1024 * 1024, {"Instruction1"});
    Program program3("Program3", 1 * 1024 * 1024, {"Instruction1"});
    Program program4("Program4", 2 * 1024 * 1024, {"Instruction1"});

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
    Program program5("Program5", 1 * 1024 * 1024, {"Instruction1"});
    Program program6("Program6", 2 * 1024 * 1024, {"Instruction1"});

    // Chargement des programmes 5 et 6
    memoryManager.loadProgram(program5);
    memoryManager.displayMemoryState();
    memoryManager.loadProgram(program6);
    memoryManager.displayMemoryState();

    // Accès mémoire pour Program5
    memoryManager.testMemoryAccess(program5, 0, false);       // Lecture instructions
    memoryManager.testMemoryAccess(program5, 524288, true);  // Ecriture données

    // Accès mémoire pour Program6
    memoryManager.testMemoryAccess(program6, 1048576, false); // Lecture instructions
    memoryManager.testMemoryAccess(program6, 2097152, true);  // Ecriture données (adresse corrigée)

    return 0;
}
