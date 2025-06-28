/*Programa que evalua dos número e indica cual es el mayor*/
#include <iostream>
int main(){
    int numero1{0};
    int numero2{0};
    std::cout<<"¡Bienvenido!\n";
    std::cout<<"Ingresa el primer número: \n";
    std::cin>>numero1;
    std::cout<<"¡Gracias! Ingresa el segundo número: \n";
    std::cin>>numero2;
    std::cout<<"Procesando...\n";
    if (numero1>numero2)
    {
        std::cout<<"El número "<<numero1<<" es mayor\n";
    }
    else if (numero2>numero1)
    {
        std::cout<<"El número "<<numero2<<" es mayor\n";
    }
    else
    {
        std::cout<<"Los números son iguales";
    }
    return 0;
}