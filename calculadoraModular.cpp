#include <iostream>

// Funciones para operaciones básicas
int suma(int a, int b) { return a + b; }
int resta(int a, int b) { return a - b; }
int multiplicacion(int a, int b) { return a * b; }
double division(int a, int b) { return (b != 0) ? static_cast<double>(a) / b : 0; }

int main() {
    int opcion{0};
    char continuar;
    
    do {
        // Mostrar menú
        std::cout << "\nBienvenido, selecciona la operación que deseas realizar:\n";
        std::cout << "(1) Suma\n(2) Resta\n(3) Multiplicación\n(4) División\n";
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;

        // Validar opción
        if (opcion < 1 || opcion > 4) {
            std::cout << "Error, opción inválida.\n";
            continue; // Volver a pedir la opción
        }

        // Pedir valores
        int a{0}, b{0};
        std::cout << "Ingrese los dos valores: \n";
        std::cout << "Valor 1: ";
        std::cin >> a;
        std::cout << "Valor 2: ";
        std::cin >> b;

        // Ejecutar la operación seleccionada
        switch (opcion) {
            case 1:
                std::cout << "La suma es: " << suma(a, b) << "\n";
                break;
            case 2:
                std::cout << "La resta es: " << resta(a, b) << "\n";
                break;
            case 3:
                std::cout << "La multiplicación es: " << multiplicacion(a, b) << "\n";
                break;
            case 4:
                if (b == 0) {
                    std::cout << "Error: No se puede dividir por cero.\n";
                } else {
                    std::cout << "La división es: " << division(a, b) << "\n";
                }
                break;
        }

        // Preguntar si quiere continuar
        std::cout << "¿Deseas realizar otra operación? (s/n): ";
        std::cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    std::cout << "Gracias por usar la calculadora.\n";
    return 0;
}
