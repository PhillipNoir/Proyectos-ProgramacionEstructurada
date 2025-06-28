/*Programa que evalúa si un número es par o impar*/
#include<iostream>
int main(){
    int numeroAEvaluar{0};
    std::cout<<"¡Bienvenido! Ingresa un numero: \n";
    std::cin>>numeroAEvaluar;
    int modulo{0};
    modulo=numeroAEvaluar%2;
    if (modulo==0)
    {
        std::cout<<"El número es par\n";
    }
    else
    {
        std::cout<<"El número es impar\n";
    }
    return 0;
}