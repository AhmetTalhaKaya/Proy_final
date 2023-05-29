#ifndef MEDICION_H
#define MEDICION_H

#include <iostream>

using namespace std;

class Medicion {
    friend ostream& operator<<(ostream& out, const Medicion& med);

public:
    float temperatura;
    float humedad;
    float precipitacion;
    float intensidadLuz;
};

ostream& operator<<(ostream& out, const Medicion& med);

#endif // MEDICION_H




