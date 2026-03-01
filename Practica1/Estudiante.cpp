#include <iostream>
#include <string>

using namespace std;

class Estudiante
{
public:
    string carnet;
    string nombre;
    string apellido;
    string carrera;
    int semestre;

    Estudiante(string _carnet, string _nombre, string _apellido, string _carrera, int _semestre)
    {
        carnet = _carnet;
        nombre = _nombre;
        apellido = _apellido;
        carrera = _carrera;
        semestre = _semestre;
    }
};
