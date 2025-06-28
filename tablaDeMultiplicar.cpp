/*Programa que solicita un número al usuario y muestra su tabla de multiplicar*/
#include<iostream>
int main(){
    int num1{0};
    int producto{0};
    std::cout<<"Bienvenido, ingrese un número: \n";
    std::cin>>num1;
    std::cout<<"La tabla de multiplicar de "<<num1<<" es:\n";
    for (int i = 1; i < 11; i++)
    {
        producto=num1*i;
        std::cout<<num1<<"*"<<i<<"="<<producto<<"\n";
    }
    return 0;
}