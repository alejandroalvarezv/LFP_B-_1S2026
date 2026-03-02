Sistema de Análisis Académico (C++)
Este software es una herramienta de consola diseñada para automatizar el procesamiento de registros académicos. Permite cargar datos masivos de estudiantes, cursos y notas desde archivos externos, realizar cálculos estadísticos de alta precisión y exportar los resultados en reportes visuales en formato HTML.

Características Principales
Carga Masiva: Procesamiento de archivos .lfp
Motor de Análisis: Función personalizada split para la extracción de tokens por comas.

Cálculos Estadísticos: Obtención de Media, Mediana y Desviación Estándar.
Ranking: Algoritmo de ordenamiento para determinar los mejores promedios (Top 10).

Instrucciones de Ejecución (Paso a Paso)
1. Compilación del Código
Asegúrese de estar en la carpeta donde se encuentran sus archivos .cpp. Abra una terminal y ejecute:

Bash
g++ main.cpp -o SistemaAnalisis
2. Preparación de los Datos
Coloque los archivos estudiantes.lfp, cursos.lfp y notas.lfp en la misma carpeta donde se encuentra el ejecutable generado (SistemaAnalisis.exe).

3. Ejecución del Programa
Inicie la aplicación con el siguiente comando:

Bash
./SistemaAnalisis

Guía de Uso
Para obtener resultados correctos, siga estrictamente este flujo de trabajo dentro del menú principal:
Carga de Archivos (Pasos 1, 2 y 3): * Seleccione la opción 1 e ingrese el nombre del archivo de estudiantes (ej: estudiantes.lfp).
Seleccione la opción 2 e ingrese el de cursos.
Seleccione la opción 3 e ingrese el de notas.
Validación de Carga (Paso 4):
Utilice la opción "Resumen de Carga" para verificar que el contador de registros sea el esperado (ej: 100 registros cargados).

Generación de Reportes:
Elija cualquiera de las opciones de reportes (Estadísticas, Rendimiento, Top 10, etc.).
El programa le notificará que el archivo .html ha sido creado exitosamente en su carpeta de trabajo.

Formato de los Archivos (.lfp)
El sistema reconoce la siguiente estructura de datos separada por comas:
Estudiantes: Carnet, Nombre, Apellido, Carrera, Semestre
Cursos: Código, Nombre, Créditos, Semestre, Carrera
Notas: Carnet, Código_Curso, Punteo, Ciclo, Año

Autor
Nombre: Alejandro Emmanuel Alvarez Velasquez
Carnet: 202404224
