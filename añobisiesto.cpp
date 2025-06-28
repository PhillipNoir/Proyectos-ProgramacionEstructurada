/*Programa que solicita un número al usuario y verifica si es bisiesto*/
#include<iostream>
int main (){
    int anio{0};
    std::cout<<"¡Bienvenido! Ingresa el año que deseas consultar: \n";
    std::cin>>anio;
    if (anio%4==0)
    {
        std::cout<<"El año "<<anio<<" es bisiesto.\n";
    }
    else if(anio%400==0)
    {
        std::cout<<"El año "<<anio<<" no es bisiesto.\n";
    }
    else
    {
        std::cout<<"El año "<<anio<<" no es bisiesto.\n";
    }
    
    return 0;

}