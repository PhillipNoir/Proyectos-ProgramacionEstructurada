/*Programa que solicita un número N al usuario y calcula la suma de los primeros N números*/
#include<iostream>
int main(){
    int num1{0};
    int suma{0};
    int i{1};
    std::cout<<"Bienvenido, ingrese un número: \n";
    std::cin>>num1;
    while (i<=num1)
    {
        suma+=i;
        i++;
    }
    std::cout<<"La suma del 1 al "<<num1<<" es "<<suma;
    return 0;
}