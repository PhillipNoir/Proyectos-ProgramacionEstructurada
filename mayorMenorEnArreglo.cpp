/*Programa que solicita al usuario 10 números y muestra el menor y el mayor*/
#include<iostream>
#include<array>
int main(){
    std::array<int,10> nums;
    for (int i = 0; i < 10; i++) //Este ciclo almacena cada número
    {
        std::cout<<"Ingresa un número: \n";
        std::cin>>nums[i];
    }
    int menor=nums[0];
    int mayor=nums[0];
    for (int i = 1; i < 10; i++) //Ciclo que evalúa cada elemento del array
    {
        if (nums[i]<menor)
        {
            menor=nums[i]; //Si el número es menor se convierte en el menor provisional
        }
        if (nums[i]>mayor)
        {
            mayor=nums[i]; //Si el número es mayor se convierte en el mayor provisional
        }
    }
    

    std::cout<<"El número mayor es "<<mayor<<" y el numero menor es "<<menor<<".";
    return 0;
}