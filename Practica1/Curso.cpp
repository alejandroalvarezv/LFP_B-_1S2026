#include <iostream>
#include <string>

using namespace std;

class Curso {
public:
    string codigo;
    string nombre;
    int creditos;
    int semestre;
    string carrera;

    Curso(string _codigo, string _nombre, int _creditos, int _semestre, string _carrera) {
        codigo = _codigo;
        nombre = _nombre;
        creditos = _creditos;
        semestre = _semestre;
        carrera = _carrera;
    }
};
