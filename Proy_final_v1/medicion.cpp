#include "medicion.h"

using namespace std;

//Esta parte funciona bien, talvez toca añadirse promedio también
ostream& operator<<(ostream& out, const Medicion& med) {
    out << "Temperatura: " << med.temperatura << " °C" << endl;
    out << "Humedad: " << med.humedad << " %" << endl;
    out << "Precipitación: " << med.precipitacion << " mm" << endl;
    out << "Intensidad de luz: " << med.intensidadLuz << " lumen" << endl;
    return out;
}


