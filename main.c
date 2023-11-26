/*

Tarea 10: Árboles Balanceados AVL

Estructuras de Datos II

Fecha de publicación: Martes 21 de noviembre de 2023
Fecha de entrega: Martes 28 de noviembre de 2023

Nombre del alumno: Lara López Fryda Renata

Nombre de usuario en omegaUp: ________________________________

*/

#include <stdio.h>
#include <ctype.h>

// IMPORTANT: Comment the next line before submitting to omegaUp
#define DEBUG

typedef struct node{
    int key;
    struct node *left;
    struct node *right;
    int fe;
    int height;
}node_t;

void insert_node();
void erase_node();
void print_height();
void print_by_level();
node_t* create_node( int key);
int height(node_t *node);
void act_height( node_t *node);
void balance_factor( node_t *node);
void right_rotation(node_t **root);
void left_rotation(node_t **root);


int main(void)  {
    // IMPORTANT: Comment the next line before submitting to omegaUp
    freopen("input.txt", "rt", stdin);
    // freopen("output.txt", "rt", stdout);

    int number_of_operations;
    scanf("%d", &number_of_operations);
    while (number_of_operations--) {
        char operation;
        scanf("\n%c", &operation);
        switch (toupper(operation)) {
            case 'I':
                insert_node();
            break;
            case 'E':   
                erase_node();
            break;
            case 'A':    
                print_height();
            break;
            case 'P':      
                print_by_level();
            break;
        }
    }
    return 0;
}

void insert_node()
{
    int value;
    scanf("%d", &value);
#ifdef DEBUG
    printf("Inserting node with value %d\n", value);
#endif
    // TODO: insert node with the specified value
}

void erase_node()
{
    int value;
    scanf("%d", &value);
#ifdef DEBUG
    printf("Erasing node with value %d\n", value);
#endif
    // TODO: erase node with the specified value
}

void print_height()
{
#ifdef DEBUG
    printf("Printing the tree's height\n");
#endif
    // TODO: print the tree's height
}

void print_by_level()
{
#ifdef DEBUG
    printf("Printing the tree's content level by level\n");
#endif
    // TODO: print the tree's content level by level
}
