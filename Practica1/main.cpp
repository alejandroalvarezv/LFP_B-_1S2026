#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "Estudiante.cpp"
#include "Curso.cpp"
#include "Nota.cpp"

using namespace std;

vector<string> separar(string linea, char delimitador) {
    vector<string> piezas;
    string pieza;
    stringstream ss(linea);
    while (getline(ss, pieza, delimitador)) {
        piezas.push_back(pieza);
    }
    return piezas;
}

int main() {
    vector<Estudiante> listaEstudiantes;
    vector<Curso> listaCursos;
    vector<Nota> listaNotas;
    int opcion;

    do {
        cout << "\n--- ANALISIS ACADEMICO ---" << endl;
        cout << "1. Cargar archivo de Estudiantes (.lfp)" << endl;
        cout << "2. Cargar archivo de Cursos (.lfp)" << endl;
        cout << "3. Cargar archivo de Notas (.lfp)" << endl;
        cout << "4. Mostrar resumen de carga" << endl;
        cout << "5. Generar Reporte: Estadisticas por curso" << endl;
        cout << "6. Generar Reporte: Rendimiento por Estudiante" << endl;
        cout << "7. Generar Reporte: Top 10 Mejores Estudiantes" << endl;
        cout << "8. Generar Reporte: Cursos con Mayor Reprobacion" << endl;
        cout << "9. Generar Reporte: Analisis por Carrera" << endl;
        cout << "10. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            cout << "Archivo Estudiantes: "; cin >> nombre;
            ifstream archivo(nombre);
            string linea;
            if (archivo.is_open()) {
                while (getline(archivo, linea)) {
                    if (linea.empty()) continue;
                    vector<string> datos = separar(linea, ',');
                    if (datos.size() == 5) {
                        listaEstudiantes.push_back(Estudiante(datos[0], datos[1], datos[2], datos[3], stoi(datos[4])));
                    }
                }
                archivo.close();
                cout << ">> Estudiantes cargados." << endl;
            }
        }
        else if (opcion == 2) {
            string nombre;
            cout << "Archivo Cursos: "; cin >> nombre;
            ifstream archivo(nombre);
            string linea;
            if (archivo.is_open()) {
                while (getline(archivo, linea)) {
                    if (linea.empty()) continue;
                    vector<string> datos = separar(linea, ',');
                    if (datos.size() == 5) {
                        listaCursos.push_back(Curso(datos[0], datos[1], stoi(datos[2]), stoi(datos[3]), datos[4]));
                    }
                }
                archivo.close();
                cout << ">> Cursos cargados." << endl;
            }
        }

        else if (opcion == 3) {
            string nombre;
            cout << "Archivo Notas: "; cin >> nombre;
            ifstream archivo(nombre);
            string linea;
            if (archivo.is_open()) {
            int contadorLocal = 0;
                while (getline(archivo, linea)) {
                    if (linea.empty()) continue;

            vector<string> datos = separar(linea, ',');

            if (datos.size() >= 5) {
                double punteo = stod(datos[2]);
                int anio = stoi(datos[4]);

                listaNotas.push_back(Nota(datos[0], datos[1], punteo, datos[3], anio));
                contadorLocal++;
            }
        }
        archivo.close();
        cout << ">> [EXITO] " << contadorLocal << " notas cargadas." << endl;
    } else {
        cout << ">> [ERROR] No se pudo abrir el archivo." << endl;
    }
}

        else if (opcion == 4) {
            cout << "\n--- RESUMEN DE DATOS ---" << endl;
            cout << "Estudiantes: " << listaEstudiantes.size() << endl;
            cout << "Cursos: " << listaCursos.size() << endl;
            cout << "Notas: " << listaNotas.size() << endl;
        }


       else if (opcion == 5) {
            ofstream reporte("Reporte_Estadisticas.html");

            reporte << "<html><head><meta charset='UTF-8'></head><body>";
            reporte << "<h1>REPORTE 1: ESTADÍSTICAS GENERALES POR CURSO</h1>";

            for (int i = 0; i < listaCursos.size(); i++) {
                vector<double> notasCurso;
                double suma = 0;
                double maximo = -1, minimo = 101;

                for (int j = 0; j < listaNotas.size(); j++) {
                    if (listaNotas[j].codigoCurso == listaCursos[i].codigo) {
                        double notaActual = listaNotas[j].punteo;
                        notasCurso.push_back(notaActual);
                        suma += notaActual;
                        if (notaActual > maximo) maximo = notaActual;
                        if (notaActual < minimo) minimo = notaActual;
                    }
                }

                int n = notasCurso.size();
                if (n > 0) {
                    double promedio = suma / n;

                    sort(notasCurso.begin(), notasCurso.end());
                    double mediana = (n % 2 == 0) ? (notasCurso[n/2 - 1] + notasCurso[n/2]) / 2.0 : notasCurso[n/2];

                    double desviacion = 0;
                    if (n > 1) {
                        double varianza = 0;
                        for(double nota : notasCurso) varianza += pow(nota - promedio, 2);
                        desviacion = sqrt(varianza / n);
                    }

                    reporte << "<h2>Curso: " << listaCursos[i].nombre << " (" << listaCursos[i].codigo << ")</h2>";
                    reporte << "<table border='1' cellpadding='5' cellspacing='0'>";
                    reporte << "<tr><td><b>Estudiantes Inscritos</b></td><td>" << n << "</td></tr>";
                    reporte << "<tr><td><b>Nota Promedio</b></td><td>" << fixed << setprecision(2) << promedio << " pts.</td></tr>";
                    reporte << "<tr><td><b>Nota Máxima</b></td><td>" << maximo << " pts.</td></tr>";
                    reporte << "<tr><td><b>Nota Mínima</b></td><td>" << minimo << " pts.</td></tr>";
                    reporte << "<tr><td><b>Mediana</b></td><td>" << mediana << " pts.</td></tr>";
                    reporte << "<tr><td><b>Desviación Estándar</b></td><td>" << desviacion << "</td></tr>";
                    reporte << "</table><br><hr>";
                }
            }

            reporte << "</body></html>";
            reporte.close();

            cout << ">> [SISTEMA] Reporte de Estadisticas generado: Reporte_Estadisticas.html" << endl;
            system("start Reporte_Estadisticas.html");
        }




        else if (opcion == 6) {
            ofstream reporte("Reporte_Estudiantes.html");

            reporte << "<html><head><meta charset='UTF-8'></head><body>";
            reporte << "<h1>REPORTE 2: RENDIMIENTO ACADÉMICO INDIVIDUAL</h1>";

            for (int i = 0; i < listaEstudiantes.size(); i++) {
                double sumaNotas = 0;
                int cursosAprobados = 0;
                int cursosReprobados = 0;
                int creditosAcumulados = 0;
                int totalNotasEstudiante = 0;

                for (int j = 0; j < listaNotas.size(); j++) {
                    if (listaNotas[j].carnetEstudiante == listaEstudiantes[i].carnet) {
                        totalNotasEstudiante++;
                        sumaNotas += listaNotas[j].punteo;
                        if (listaNotas[j].punteo >= 61) {
                            cursosAprobados++;
                            for (int k = 0; k < listaCursos.size(); k++) {
                                if (listaCursos[k].codigo == listaNotas[j].codigoCurso) {
                                    creditosAcumulados += listaCursos[k].creditos;
                                    break;
                                }
                            }
                        } else {
                            cursosReprobados++;
                        }
                    }
                }

                if (totalNotasEstudiante > 0) {
                    reporte << "<h2>Estudiante: " << listaEstudiantes[i].nombre << " " << listaEstudiantes[i].apellido << "</h2>";
                    reporte << "<table border='1' cellpadding='5' cellspacing='0' width='100%'>";
                    reporte << "<tr><td bgcolor='#f2f2f2'><b>Carnet:</b></td><td>" << listaEstudiantes[i].carnet << "</td>"
                            << "<td bgcolor='#f2f2f2'><b>Carrera:</b></td><td>" << listaEstudiantes[i].carrera << "</td></tr>";

                    reporte << "<tr><td><b>Promedio General:</b></td><td>" << fixed << setprecision(2) << (sumaNotas / totalNotasEstudiante) << " pts.</td>"
                            << "<td><b>Créditos Acumulados:</b></td><td>" << creditosAcumulados << "</td></tr>";

                    reporte << "<tr><td><b>Cursos Aprobados:</b></td><td style='color:green;'>" << cursosAprobados << "</td>"
                            << "<td><b>Cursos Reprobados:</b></td><td style='color:red;'>" << cursosReprobados << "</td></tr>";
                    reporte << "</table><br><hr>";
                }
            }

            reporte << "</body></html>";
            reporte.close();

            cout << ">> [SISTEMA] Reporte de Rendimiento generado: Reporte_Estudiantes.html" << endl;
            system("start Reporte_Estudiantes.html");
        }




        else if (opcion == 7) {
            struct NodoRanking {
                string carnet;
                string nombreCompleto;
                string carrera;
                int semestre;
                double promedio;
            };
            vector<NodoRanking> ranking;

            for (int i = 0; i < listaEstudiantes.size(); i++) {
                double suma = 0;
                int contador = 0;
                for (int j = 0; j < listaNotas.size(); j++) {
                    if (listaNotas[j].carnetEstudiante == listaEstudiantes[i].carnet) {
                        suma += listaNotas[j].punteo;
                        contador++;
                    }
                }
                if (contador > 0) {
                    ranking.push_back({
                        listaEstudiantes[i].carnet,
                        listaEstudiantes[i].nombre + " " + listaEstudiantes[i].apellido,
                        listaEstudiantes[i].carrera,
                        listaEstudiantes[i].semestre,
                        suma / contador
                    });
                }
            }

            for (int i = 0; i < ranking.size(); i++) {
                for (int j = i + 1; j < ranking.size(); j++) {
                    if (ranking[j].promedio > ranking[i].promedio) {
                        swap(ranking[i], ranking[j]);
                    }
                }
            }

            ofstream reporte("Reporte_Top10.html");
            reporte << "<html><head><meta charset='UTF-8'></head><body>";
            reporte << "<h1 align='center'>🏆 TOP 10 MEJORES ESTUDIANTES 🏆</h1>";

            reporte << "<table border='1' cellpadding='10' cellspacing='0' align='center' width='90%'>";
            reporte << "<tr bgcolor='#34495e' style='color:white;'>"
                    << "<th>Posición</th><th>Carnet</th><th>Nombre Completo</th><th>Carrera</th><th>Promedio</th></tr>";

            for (int i = 0; i < ranking.size() && i < 10; i++) {
                string colorFila = "";
                if (i == 0) colorFila = "bgcolor='#fff9c4'";
                else if (i == 1) colorFila = "bgcolor='#f5f5f5'";
                else if (i == 2) colorFila = "bgcolor='#fdf2e9'";

                reporte << "<tr " << colorFila << " align='center'>"
                        << "<td><b>" << (i + 1) << "</b></td>"
                        << "<td>" << ranking[i].carnet << "</td>"
                        << "<td align='left'>" << ranking[i].nombreCompleto << "</td>"
                        << "<td>" << ranking[i].carrera << "</td>"
                        << "<td><b>" << fixed << setprecision(2) << ranking[i].promedio << " pts.</b></td>"
                        << "</tr>";
            }

            reporte << "</table>";
            reporte << "<p align='center'><i>Reporte generado automáticamente por el Sistema de Análisis Académico</i></p>";
            reporte << "</body></html>";
            reporte.close();

            cout << ">> [EXITO] Ranking generado: Reporte_Top10.html" << endl;
            system("start Reporte_Top10.html");
        }





            else if (opcion == 8) {
            struct NodoReprobacion {
                string codigo;
                string nombre;
                int total;
                int aprobados;
                int reprobados;
                double porcentaje;
            };
            vector<NodoReprobacion> rankingCursos;

            for (int i = 0; i < listaCursos.size(); i++) {
                int aprob = 0, reprob = 0;
                for (int j = 0; j < listaNotas.size(); j++) {
                    if (listaNotas[j].codigoCurso == listaCursos[i].codigo) {
                        if (listaNotas[j].punteo >= 61) aprob++;
                        else reprob++;
                    }
                }
                int total = aprob + reprob;
                if (total > 0) {
                    double porc = (reprob * 100.0) / total;
                    rankingCursos.push_back({listaCursos[i].codigo, listaCursos[i].nombre, total, aprob, reprob, porc});
                }
            }

            for (int i = 0; i < rankingCursos.size(); i++) {
                for (int j = i + 1; j < rankingCursos.size(); j++) {
                    if (rankingCursos[j].porcentaje > rankingCursos[i].porcentaje) {
                        swap(rankingCursos[i], rankingCursos[j]);
                    }
                }
            }

            ofstream reporte("Reporte_Reprobacion.html");
            reporte << "<html><head><meta charset='UTF-8'></head><body>";
            reporte << "<h1 align='center'>⚠️ ANÁLISIS DE REPROBACIÓN POR CURSO ⚠️</h1>";
            reporte << "<p align='center'>Cursos ordenados por el mayor índice de pérdida académica.</p>";

            reporte << "<table border='1' cellpadding='8' cellspacing='0' align='center' width='95%'>";
            reporte << "<tr bgcolor='#2c3e50' style='color:white;'>"
                    << "<th>CÓDIGO</th><th>NOMBRE DEL CURSO</th><th>TOTAL</th><th>APROBADOS</th><th>REPROBADOS</th><th>% ÍNDICE</th></tr>";

            for (const auto& c : rankingCursos) {
                string colorFila = (c.porcentaje >= 50.0) ? "bgcolor='#fdedec'" : "";
                string colorTexto = (c.porcentaje >= 50.0) ? "color='red'" : "color='green'";

                reporte << "<tr " << colorFila << " align='center'>"
                        << "<td>" << c.codigo << "</td>"
                        << "<td align='left'>" << c.nombre << "</td>"
                        << "<td>" << c.total << "</td>"
                        << "<td>" << c.aprobados << "</td>"
                        << "<td>" << c.reprobados << "</td>"
                        << "<td><font " << colorTexto << "><b>" << fixed << setprecision(2) << c.porcentaje << "%</b></font></td>"
                        << "</tr>";
            }

            reporte << "</table>";
            reporte << "</body></html>";
            reporte.close();

            cout << ">> [SISTEMA] Reporte de Reprobacion generado: Reporte_Reprobacion.html" << endl;
            system("start Reporte_Reprobacion.html");
        }





        else if (opcion == 9) {
            ofstream reporte("Reporte_Carreras.html");

            reporte << "<html><head><meta charset='UTF-8'></head><body>";
            reporte << "<h1 align='center'>REPORTE 5: ANÁLISIS INTEGRAL POR CARRERA</h1>";

            vector<string> carrerasYaProcesadas;

            for (int i = 0; i < listaEstudiantes.size(); i++) {
                string carreraActual = listaEstudiantes[i].carrera;

                bool yaEsta = false;
                for (string c : carrerasYaProcesadas) if (c == carreraActual) yaEsta = true;
                if (yaEsta) continue;

                int totalEstudiantes = 0, totalNotasCarrera = 0, cursosDisponibles = 0;
                double sumaNotasCarrera = 0;
                int semestres[11] = {0};

                for (int j = 0; j < listaEstudiantes.size(); j++) {
                    if (listaEstudiantes[j].carrera == carreraActual) {
                        totalEstudiantes++;
                        int sem = listaEstudiantes[j].semestre;
                        if (sem >= 1 && sem <= 10) semestres[sem]++;

                        for (int k = 0; k < listaNotas.size(); k++) {
                            if (listaNotas[k].carnetEstudiante == listaEstudiantes[j].carnet) {
                                sumaNotasCarrera += listaNotas[k].punteo;
                                totalNotasCarrera++;
                            }
                        }
                    }
                }

                for (int j = 0; j < listaCursos.size(); j++) {
                    if (listaCursos[j].carrera == carreraActual) cursosDisponibles++;
                }

                reporte << "<h2>Carrera: " << carreraActual << "</h2>";

                reporte << "<table border='1' cellpadding='10' cellspacing='0' width='100%' bgcolor='#f9f9f9'>";
                reporte << "<tr>"
                        << "<td><b>Total Estudiantes:</b> " << totalEstudiantes << "</td>"
                        << "<td><b>Cursos en Pensum:</b> " << cursosDisponibles << "</td>"
                        << "<td><b>Promedio de Carrera:</b> " << fixed << setprecision(2)
                        << (totalNotasCarrera > 0 ? (sumaNotasCarrera / totalNotasCarrera) : 0.0) << " pts.</td>"
                        << "</tr></table>";

                reporte << "<h3>Distribución por Semestre</h3>";

                reporte << "<table border='1' cellpadding='5' cellspacing='0' width='50%'>";
                reporte << "<tr bgcolor='#ecf0f1'><th>Semestre</th><th>Cantidad de Alumnos</th><th>Porcentaje</th></tr>";

                for (int s = 1; s <= 10; s++) {
                    if (semestres[s] > 0) {
                        double porcSemestre = (semestres[s] * 100.0) / totalEstudiantes;
                        reporte << "<tr align='center'>"
                                << "<td>Semestre " << s << "</td>"
                                << "<td>" << semestres[s] << "</td>"
                                << "<td>" << fixed << setprecision(1) << porcSemestre << "%</td>"
                                << "</tr>";
                    }
                }
                reporte << "</table><br><hr>";

                carrerasYaProcesadas.push_back(carreraActual);
            }

            reporte << "</body></html>";
            reporte.close();

            cout << ">> [SISTEMA] Analisis por Carrera generado: Reporte_Carreras.html" << endl;
            system("start Reporte_Carreras.html");
        }




    } while (opcion != 10);

    return 0;
}
