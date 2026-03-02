#include <iostream>
#include <string>

using namespace std;

class Nota {
public:
    string carnetEstudiante;
    string codigoCurso;
    double punteo;
    string semestre;
    int anio;

    Nota(string _carnet, string _codigo, double _punteo, string _semestre, int _anio) {
        carnetEstudiante = _carnet;
        codigoCurso = _codigo;
        punteo = _punteo;
        semestre = _semestre;
        anio = _anio;
    }
};
