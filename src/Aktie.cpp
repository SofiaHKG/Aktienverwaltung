#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Aktie.h"
#include <cmath>

void Aktie::importStock() {
    std::string filename;
    std::cout << "Geben Sie den Namen der CSV-Datei ein: ";
    std::getline(std::cin, filename);


    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "\nKonnte Datei " << filename << " nicht oeffnen.\n" << std::endl;
        return;
    }

    /*
    // for debugging
    std::cout << "Importiere Kursdaten fuer " << filename << std::endl;
    */

    std::string line;
    std::getline(file, line); // Überspringe die Kopfzeile

    while (std::getline(file, line)) {
        std::istringstream s(line);
        Kursdaten kursdaten;
        std::string field;

        std::getline(s, kursdaten.date, ',');
        std::getline(s, field, ','); kursdaten.open = std::stof(field);
        std::getline(s, field, ','); kursdaten.high = std::stof(field);
        std::getline(s, field, ','); kursdaten.low = std::stof(field);
        std::getline(s, field, ','); kursdaten.close = std::stof(field);
        std::getline(s, field, ','); kursdaten.adjClose = std::stof(field);
        std::getline(s, field, ','); kursdaten.volume = std::stoi(field);

        this->kursdaten.push_back(kursdaten); // Füge die geparsten Kursdaten zur Liste hinzu
        /*
        // for debugging
        std::cout << "Hinzugefuegte Kursdaten: " << kursdaten.date << std::endl;
        */
    }

    /*
    // for debugging
    std::cout << "Anzahl der importierten Kursdatensaetze: " << this->kursdaten.size() << std::endl;
    */

    file.close();
    std::cout << "\nImport von " << filename << " erfolgreich abgeschlossen.\n" << std::endl;
}

void Aktie::printPlot() {
    std::cout << "\nChart for symbol " + this->kuerzel + ": \n";

    int latestIndex = kursdaten.size()-1;

    float maxClose = kursdaten[latestIndex].close;
    float minClose = kursdaten[latestIndex].close;

    for (int i = latestIndex; i > latestIndex-30; i--) {
        if (kursdaten[i].close > maxClose) {
            maxClose = kursdaten[i].close+1;
        } else if (kursdaten[i].close < minClose) {
            minClose = kursdaten[i].close-1;
        }
    }

    std::cout << "Max: " << std::floor(maxClose) << " Min: " << std::floor(minClose) << std::endl;

    for (int i = std::floor(maxClose); i > std::floor(minClose); i--) {
        for (int j = latestIndex-30; j <= latestIndex; j++) {
            if (std::floor(kursdaten[j].close) == i) {
                std::cout << "x ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }


}

