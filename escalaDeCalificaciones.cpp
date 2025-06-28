/*Programa que solicite una calificación (0-100) e indicar si es MB (90-100), B (80-89), S (60-79), NA (0-59).*/
#include <iostream>
int main(){
    int calif{0};
    std::cout<<"¡Bienvenido! Ingrese su calificación: \n";
    std::cin>>calif;
    if (calif<60)
    {
        std::cout<<"Tienes NA";
    }
    else if (calif>59 && calif<80)
    {
        std::cout<<"Tienes S";
    }
    else if (calif>79 && calif<90)
    {
        std::cout<<"Tienes B";
    }
    else if (calif>89 && calif<101)
    {
        std::cout<<"Tienes MB";
    }
    return 0;
}