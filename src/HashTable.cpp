#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Initializes the vector with HashEntrys
void HashTable::initVector() {
    for (int i = 0; i <= tableSize; i++) {
        table.push_back(HashEntry()); //HashEntry() -> isActive = false, so it's an empty HashEntry
    }
}

// djb2 - Hashfunktion
unsigned int HashTable::hashFunction(const std::string& key) const {
    unsigned long hash = 5381;
    for (auto c : key) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % tableSize;
}

// Quadratische Sondierung zur Kollisionsbehandlung
void HashTable::quadraticProbing(const std::string& key, unsigned int& i) const {
    unsigned int index = hashFunction(key);
    int attempt = 0;
    while (table[index].isActive && table[index].key != key) {
        attempt++;
        index = (index + attempt * attempt) % tableSize; // Berechne neuen Index
    }
    i = index; // Finde den Index für die Einfügung oder das gefundene Element
}

// Löschen einer Aktie
void HashTable::delAktie(const std::string& key) {
    unsigned int index;
    quadraticProbing(key, index);

    if (table[index].isActive && table[index].key == key) {
        table[index].isActive = false; // Direkter Zugriff mit .
        std::cout << "\nAktie " << key << " wurde geloescht.\n";
    } else {
        std::cerr << "\nAktie nicht gefunden.\n";
    }
}

// Suchen einer Aktie
Aktie* HashTable::searchAktie(const std::string& key) {
    unsigned int index;
    quadraticProbing(key, index);

    if (table[index].isActive && table[index].key == key) {
        return &table[index].aktie; // Direkter Zugriff mit .
    } else {
        return nullptr; // Aktie nicht gefunden
    }
}

// Add Aktie
void HashTable::addAktie(const Aktie& aktie) {
    unsigned int index;
    this->quadraticProbing(aktie.kuerzel, index); // Berechne den Index für das Kürzel der Aktie

    // Überprüfe, ob der berechnete Index bereits belegt ist und ob Kollision auftritt
    if (!table[index].isActive) {
        table[index] = HashEntry(aktie.kuerzel, aktie, true); // Füge die Aktie hinzu, wenn der Slot frei ist
    } else {
        // Hier könnte man erweiterte Kollisionsbehandlung implementieren
        std::cerr << "Kollision aufgetreten beim Hinzufügen der Aktie: " << aktie.kuerzel << std::endl;
    }
}

void HashTable::saveTable() {

    std::string filename = "hashtable.csv";

    std::ofstream file(filename);

    for (int i = 0; i <= tableSize; i++) {
        if (table[i].isActive) {
            file << table[i].aktie.name << "," << table[i].aktie.wkn << "," << table[i].aktie.kuerzel << "\n";
        }
    }

    file.close();

    std::cout << "\nHashtable erfolgreich in hashtable.csv gespeichert\n";
}

void HashTable::loadTable() {

    std::string filename = "hashtable.csv";
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream s(line);
        Aktie aktie;

        std::getline(s, aktie.name, ',');
        std::getline(s, aktie.wkn, ',');
        std::getline(s, aktie.kuerzel, ',');

        addAktie(aktie);
    }

    file.close();

    std::cout << "\nAktie erfolgreich geladen!\n";
}
