# Tarea Semana 9: Manipulación de Archivos CSV en C++

## Descripción del problema
Este programa automatiza la lectura y validación del archivo de catálogo de productos `productos.csv`. Detecta registros inválidos mediante control de excepciones (`try/catch`), calcula el total del inventario para productos válidos y genera un reporte de texto automatizado con los resultados.

## Estructura del CSV
El archivo original debe situarse en la ruta `datos/productos.csv` y contener la cabecera:
`codigo,nombre,precio,existencia`

## Instrucciones de Ejecución
1. Asegurarse de tener creada la carpeta `datos` y la carpeta `reportes` en el mismo directorio donde está el `main.cpp`. (Este ZIP ya contiene la estructura armada).
2. Compilar usando C++17: `g++ -std=c++17 main.cpp -o inventario`
3. Ejecutar el archivo generado: `./inventario` (Linux/Mac) o `inventario.exe` (Windows).
4. El sistema pedirá buscar un código (por ejemplo: "P003" o "P999").
5. Verificar el resultado escrito en `reportes/resumen.txt`.

## Decisiones de Validación
* **Manejo de vacíos:** Se empleó la condición `string::empty()` para los campos de texto `codigo` y `nombre`.
* **Manejo de tipos:** Se usaron `stod()` y `stoi()` para convertir texto a número. Para evitar cuelgues (crashes) provocados por letras ("abc"), la conversión se realizó enteramente dentro de un bloque `try/catch`. 
* **Rangos:** Se evaluó con operadores lógicos (`<= 0` y `< 0`) para detectar precios y existencias inconsistentes.
