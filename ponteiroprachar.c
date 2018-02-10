//Programa que ilustra que um ponteiro pra char aponta para o primeiro endereço da minha string
#include <stdio.h>


int main()
{
    char *charPtr = "Minha String";
    printf("%s\n", charPtr);
    printf("%p\n", charPtr); // para printar endereços eu uso %p
    
    while(*charPtr)
    {
        printf("O conteudo do endereço %p é: %c\n", charPtr, *charPtr);
        ++charPtr;
    }   

    return 0; 
}