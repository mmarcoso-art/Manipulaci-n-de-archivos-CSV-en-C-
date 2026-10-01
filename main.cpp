#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // 1. Abrir datos/productos.csv de forma segura
    ifstream archivo("datos/productos.csv");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo datos/productos.csv" << endl;
        return 1;
    }

    string linea, codigo, nombre, precioTexto, existenciaTexto;
    int validos = 0, invalidos = 0;
    double valorTotalInventario = 0.0;

    // 2. Leer el archivo y omitir el encabezado antes de procesar
    if (getline(archivo, linea)) {
        // Encabezado omitido
    }

    // Solicitar al usuario el código a buscar
    cout << "Ingrese el codigo del producto a buscar: ";
    string codigoBuscar;
    cin >> codigoBuscar;
    
    bool encontrado = false;
    string resultadoBusqueda = "El producto con codigo " + codigoBuscar + " no existe en el inventario.";

    // Leer linea por linea
    while (getline(archivo, linea)) {
        // 3. Separar los campos con stringstream usando la coma
        stringstream ss(linea);
        getline(ss, codigo, ',');
        getline(ss, nombre, ',');
        getline(ss, precioTexto, ',');
        getline(ss, existenciaTexto, ',');

        bool registroValido = true;
        double precio = 0.0;
        int existencia = 0;

        // 4. Validar filas: campos vacíos
        if (codigo.empty() || nombre.empty()) {
            registroValido = false;
        } else {
            // Conversión protegida para números
            try {
                precio = stod(precioTexto);
                existencia = stoi(existenciaTexto);
                
                // Validar rangos numéricos
                if (precio <= 0 || existencia < 0) {
                    registroValido = false;
                }
            } catch (...) {
                // Si falla stod o stoi, es inválido
                registroValido = false;
            }
        }

        // 5. Contar registros y 6. Calcular total
        if (registroValido) {
            validos++;
            valorTotalInventario += (precio * existencia);

            // 7. Buscar si el código coincide
            if (codigo == codigoBuscar) {
                encontrado = true;
                resultadoBusqueda = "Encontrado: " + nombre + " | Precio: Q" + to_string(precio) + " | Existencia: " + to_string(existencia);
            }
        } else {
            invalidos++; 
        }
    }

    // Cerrar archivo de lectura
    archivo.close();

    // Mostrar el resultado de la búsqueda al usuario
    cout << "\n--- Resultado de Busqueda ---\n";
    cout << resultadoBusqueda << "\n\n";

    // 8. Generar reportes/resumen.txt
    ofstream reporte("reportes/resumen.txt");
    if (reporte.is_open()) {
        reporte << "=== REPORTE DE INVENTARIO ===\n";
        reporte << "Total de registros validos: " << validos << "\n";
        reporte << "Total de registros invalidos: " << invalidos << "\n";
        reporte << fixed << setprecision(2);
        reporte << "Valor total del inventario: Q" << valorTotalInventario << "\n\n";
        reporte << "=== RESULTADO DE BUSQUEDA ===\n";
        reporte << resultadoBusqueda << "\n";
        
        reporte.close();
        cout << "Reporte generado exitosamente en 'reportes/resumen.txt'." << endl;
    } else {
        cout << "Error: No se pudo crear el archivo de reporte en 'reportes/resumen.txt'." << endl;
    }

    return 0;
}
