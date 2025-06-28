/*Programa que solicita un número al usuario y calcula su factorial*/
#include<iostream>
int main(){
    int num1{0};
    int factorial{1};
    std::cout<<"Bienvenido, ingrese un número: \n";
    std::cin>>num1;
    for (int i = 1; i <=num1; i++)
    {
        factorial*=i;
    }
    std::cout<<"El factorial de "<<num1<<" es "<<factorial;
    return 0;
}