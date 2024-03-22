#ifndef KURSDATEN_H
#define KURSDATEN_H

#include <string>

struct Kursdaten {
    std::string date;   // Datum als String
    float open;         // Er�ffnungskurs
    float high;         // H�chstkurs
    float low;          // Tiefstkurs
    float close;        // Schlusskurs
    float adjClose;     // Angepasster Schlusskurs
    int volume;         // Handelsvolumen
};
#endif // KURSDATEN_H

