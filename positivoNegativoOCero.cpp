/*Programa que evalua si el número ingresado es positivo, negativo o cero*/
#include<iostream>
int main(){
int num{0};
std::cout<<"¡Bienvenido! Ingresa un número: \n";
std::cin>>num;
std::cout<<"Analizando...\n";
if (num>0)
{
    std::cout<<"El número "<<num<<" es positivo\n";
}
else if (num<0)
{
    std::cout<<"El número "<<num<<" es negativo\n";
}
else
{
    std::cout<<"El número ingresado es 0";
}
return 0;
}