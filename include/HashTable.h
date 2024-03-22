#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Aktie.h"
#include <vector>
#include <string>

class HashTable {
private:
    struct HashEntry {
        std::string key;
        Aktie aktie;
        bool isActive; // Wird verwendet, um zu markieren, ob der Eintrag belegt (true) oder frei (false) ist

        HashEntry() : isActive(false) {}
        HashEntry(const std::string& key, const Aktie& aktie, bool isActive) : key(key), aktie(aktie), isActive(isActive) {}
    };

    std::vector<HashEntry> table;
    int tableSize = 2003; // Wähle eine geeignete Größe für die Hashtabelle

public:
    HashTable() : table(tableSize) {}


    void initVector();
    void addAktie(const Aktie& aktie);
    void delAktie(const std::string& key);
    Aktie* searchAktie(const std::string& key);
    unsigned int hashFunction(const std::string& key) const;
    void quadraticProbing(const std::string& key, unsigned int& i) const;
    void saveTable();
    void loadTable();
};

#endif // HASHTABLE_H

