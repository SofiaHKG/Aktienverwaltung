#ifndef AKTIE_H
#define AKTIE_H

#include "Kursdaten.h"
#include <string>
#include <vector>

class Aktie
{
public:
    std::string name;
    std::string wkn;
    std::string kuerzel;
    std::vector<Kursdaten> kursdaten;

    void importStock();
    void printPlot();
};

#endif // AKTIE_H
