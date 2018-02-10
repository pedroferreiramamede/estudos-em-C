#include <stdio.h>
#include <stdlib.h>

//Crio um nó da minha lista, uma caixinha para a Pati s2 entender
struct node
{
    char *x;
    struct node *next;
};

int main(int argc, char *argv[])
{
    //Crio um ponteiro que aponta par o inicio da minha lista, que será o meu primeiro nó
    struct node *inicio;
    //Crio um outro ponteiro que irá percorrer a minha lista
    struct node *listPtr;

    //Crio o primeiro nó
    inicio = malloc( sizeof(struct node) );
    inicio->x = argv[1];
    inicio->next = 0;

    listPtr = inicio;

    if(listPtr->next != 0)
    {
        while(listPtr->next != 0)
        {
            listPtr = listPtr->next; //Enquanto eu nao chegar no fim da lista, eu vou par ao próximo nó
        }
    }
    //Agora eu estou no fim da lista com certeza
    //Entao vou criar um novo nó
    
    int argumentos = 1;
    while(argumentos < argc)
    {
        listPtr->next = malloc( sizeof(struct node) ); //Crio o novo nó

        listPtr = listPtr->next; // Agora meu listPtr está apontando para o meu novo nó

        if ( listPtr == 0 ){ printf("Out of memory"); return 0; }

        listPtr->next = 0; //Digo que ele é o ultimo
        listPtr->x = (char*) argv[argumentos+1];

        ++argumentos;
    }
    
    
    
    //Printo a minha lista
    listPtr = inicio;
    while(listPtr)
    {
        printf("O endereço %p contém o valor: %s\n", listPtr, listPtr->x);
        listPtr = listPtr->next;
    }


    return 0;
}