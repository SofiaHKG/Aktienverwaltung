#include <iostream>
#include "Aktie.h"
#include "HashTable.h"

int main() {
    // Initialisierung der Hashtabelle und weiterer notwendiger Variablen
    HashTable meineHashTable;   // Instanz der Hashtabelle
    meineHashTable.initVector();

    char auswahl;
    do {
        std::cout << "\n1. ADD, 2. DEL, 3. IMPORT, 4. SEARCH, 5. PLOT, 6. SAVE, 7. LOAD, 8. QUIT\nAuswahl: ";
        std::cin >> auswahl;
        // Bereinige den Input-Stream nach der Auswahl
        std::cin.ignore(); // Ignoriert den newline Charakter nach der Eingabe

        switch(auswahl) {
            case '1': { // ADD
                std::string name, wkn, kuerzel;
                std::cout << "Geben Sie den Namen der Aktie ein: ";
                std::getline(std::cin, name);
                std::cout << "Geben Sie die WKN der Aktie ein: ";
                std::getline(std::cin, wkn);
                std::cout << "Geben Sie das Kuerzel der Aktie ein: ";
                std::getline(std::cin, kuerzel);

                // Erstelle ein neues Aktie-Objekt mit den eingegebenen Daten
                Aktie neueAktie;
                neueAktie.name = name;
                neueAktie.wkn = wkn;
                neueAktie.kuerzel = kuerzel;


                // Füge das neue Aktie-Objekt zur Hashtabelle hinzu
                meineHashTable.addAktie(neueAktie);

                std::cout << "\nAktie " << neueAktie.name << " (" << neueAktie.kuerzel << ") erfolgreich hinzugefuegt.\n" << std::endl;
                break;
                }
            case '2': { // DEL
                std::string key;
                std::cout << "Geben Sie das Kuerzel der Aktie ein, die Sie loeschen moechten: ";
                std::getline(std::cin, key);
                meineHashTable.delAktie(key);
                break;
                }
            case '3': { // IMPORT
                std::string key;
                std::cout << "Geben Sie das Kuerzel der Aktie ein, fuer die Sie Kursdaten importieren moechten: ";
                std::getline(std::cin, key);

                // Suche der Aktie in der Hashtabelle
                Aktie* gefundeneAktie = meineHashTable.searchAktie(key);
                if (gefundeneAktie != nullptr) {
                    // Wenn die Aktie gefunden wurde, rufe die importStock Methode auf
                    gefundeneAktie->importStock();
                } else {
                    std::cout << "\nAktie mit dem Kuerzel " << key << " nicht gefunden.\n" << std::endl;
                }
                break;
                }

            case '4': { // SEARCH
                std::string key;
                std::cout << "Geben Sie das Kuerzel der Aktie ein, die sie suchen moechten: ";
                std::getline(std::cin, key);
                Aktie* gefundeneAktie = meineHashTable.searchAktie(key);
                if (gefundeneAktie != nullptr) {
                    std::cout << "\nAktie gefunden: \n";
                    std::cout << "Name: " << gefundeneAktie->name << "\n";
                    std::cout << "WKN: " << gefundeneAktie->wkn << "\n";
                    std::cout << "Kuerzel: " << gefundeneAktie->kuerzel << "\n";

                    // Überprüfen, ob Kursdaten vorhanden sind
                    if (!gefundeneAktie->kursdaten.empty()) {
                        const Kursdaten& neuesteKursdaten = gefundeneAktie->kursdaten.back(); // Letzter Eintrag = aktuellste Kursdaten
                        std::cout << "\nAktuellste Kursdaten:\n"
                                  << "Datum: " << neuesteKursdaten.date << "\n"
                                  << "Open: " << neuesteKursdaten.open << "\n"
                                  << "High: " << neuesteKursdaten.high << "\n"
                                  << "Low: " << neuesteKursdaten.low << "\n"
                                  << "Close: " << neuesteKursdaten.close << "\n"
                                  << "Volume: " << neuesteKursdaten.volume << "\n"
                                  << "Adj Close: " << neuesteKursdaten.adjClose << std::endl;
                    } else {
                        std::cout << "Keine Kursdaten vorhanden.\n";
                    }

                } else {
                    std::cout << "\nAktie mit dem Kuerzel " << key << " nicht gefunden.\n";
                }
                break;
            }

            case '5': {
                // PLOT
                std::string key;
                std::cout << "Geben Sie das Kuerzel der Aktie ein: ";
                std::getline(std::cin, key);
                Aktie* gefundeneAktie = meineHashTable.searchAktie(key);
                if (gefundeneAktie != nullptr) {
                    std::cout << "\nAktie gefunden: \n";
                    std::cout << "Name: " << gefundeneAktie->name << "\n";
                    std::cout << "WKN: " << gefundeneAktie->wkn << "\n";
                    std::cout << "Symbol: " << gefundeneAktie->kuerzel << "\n";

                    // Überprüfen, ob Kursdaten vorhanden sind
                    if (!gefundeneAktie->kursdaten.empty()) {
                        gefundeneAktie->printPlot();

                    } else {
                        std::cout << "Keine Kursdaten vorhanden.\n";
                    }

                } else {
                    std::cout << "\nAktie mit dem Kuerzel " << key << " nicht gefunden.\n";
                }
                break;
            }
            case '6': {
                // SAVE
                meineHashTable.saveTable();
                break;
            }
            case '7':
                // LOAD
                meineHashTable.loadTable();
                break;
            case '8':
                std::cout << "Programm wird beendet...\n";
                break;
            default:
                std::cout << "\nUngueltige Eingabe\n";
        }
    } while (auswahl != '8');

    return 0;
}

