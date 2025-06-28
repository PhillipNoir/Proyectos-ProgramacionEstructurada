/*Programa que solicita la edad al usuario e indica si es apto para votar.*/
#include<iostream>
int main(){
    int edad{0};
    std::cout<<"¡Bienvenido! Ingresa tu edad: \n";
    std::cin>>edad;
    if (edad>17)
    {
        std::cout<<"Puedes votar\n";
    }
    else
    {
        std::cout<<"Eres menor de edad, no puedes votar\n";
    }
    return 0;
}