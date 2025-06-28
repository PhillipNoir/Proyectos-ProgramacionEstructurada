#include <iostream>

int main() {
    int num;
    
    std::cout << "Ingrese un número entero positivo: ";
    std::cin >> num;

    if (num <= 0) {
        std::cout << "Por favor, ingrese un número entero positivo." << std::endl;
        return 1;  // Código de error
    }

    int contador = 0;
    int temp = num;  // Variable auxiliar para no modificar num

    while (temp > 0) {
        temp /= 10;  // Dividimos entre 10 para reducir el número
        contador++;   // Incrementamos el contador de dígitos
    }

    std::cout << "El número " << num << " tiene " << contador << " dígitos." << std::endl;

    return 0;
}
