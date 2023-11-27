/*

Tarea 10: Árboles Balanceados AVL

Estructuras de Datos II

Fecha de publicación: Martes 21 de noviembre de 2023
Fecha de entrega: Martes 28 de noviembre de 2023

Nombre del alumno: Lara López Fryda Renata

Nombre de usuario en omegaUp: ________________________________

*/

#include <stdio.h>
#include <stdlib.h>
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

typedef struct queue_node{
    node_t *avl_node;
    struct queue_node *next;
}queue_node_t;

typedef struct queue{
    queue_node_t *front;
    queue_node_t *rear;
}queue_t;

void insert_node( node_t **root);
void erase_node( node_t **root);
void print_height(node_t *root);
void print_by_level(node_t *root);
node_t* create_node( int key);
int height(node_t *node);
int balance_factor( node_t *node);
void right_rotation(node_t **root);
void left_rotation(node_t **root);
void aux_insert(node_t **root, int value);
void free_tree(node_t* root);

queue_t* createQueue();
void enqueue(queue_t* queue, node_t* treeNode);
queue_node_t* createQueueNode(node_t* treeNode);
int is_empty(queue_t *queue);

int main(void)  {
    // IMPORTANT: Comment the next line before submitting to omegaUp
    freopen("input.txt", "rt", stdin);
    // freopen("output.txt", "rt", stdout);

    node_t *root = NULL;
    int number_of_operations;
    scanf("%d", &number_of_operations);
    while (number_of_operations--) {
        char operation;
        scanf("\n%c", &operation);
        switch (toupper(operation)) {
            case 'I':
                insert_node(&root);
            break;
            case 'E':   
                erase_node(&root);
            break;
            case 'A':    
                print_height(root);
            break;
            case 'P':      
                print_by_level(root);
            break;
        }
    }
    free_tree(root);
    return 0;
}

void insert_node( node_t **root)
{
    int value;
    scanf("%d", &value);
#ifdef DEBUG
    printf("Inserting node with value %d\n", value);
#endif
    // TODO: insert node with the specified value
    aux_insert(&(*root), value);
}

void erase_node( node_t **root)
{
    int value;
    scanf("%d", &value);
#ifdef DEBUG
    printf("Erasing node with value %d\n", value);
#endif
    // TODO: erase node with the specified value
}

void print_height(node_t *root)
{
#ifdef DEBUG
    printf("Printing the tree's height\n");
#endif
    // TODO: print the tree's height
    printf("%d\n", root->height);
}

void print_by_level(node_t *root)
{
#ifdef DEBUG
#endif
    // TODO: print the tree's content level by level
    if(root == NULL){
        printf("\n");
        return;
    }
    queue_t *queue = createQueue();
    enqueue(queue, root);

    while(is_empty(queue) == 0){
        int actual_level = queue->front->avl_node->key;

        while(is_empty(queue) == 0 && queue->front->avl_node->key == actual_level){
            node_t *current = queue->front->avl_node;
            printf("%d ", current->key);

            if(current->left != NULL){
                enqueue(queue, current->left);
            }

            if(current->right != NULL){
                enqueue(queue, current->right);
            }

            queue_node_t* tmp = queue->front;
            queue->front = queue->front->next;
            free(tmp);
        }
    }
    printf("\n");
    free(queue);
}

node_t* create_node( int key)
{
    node_t *new = (node_t*)malloc(sizeof(node_t));
    new->key = key;
    new->left = new->right = NULL;
    new->fe = new->height = 0;
    return new;
}

void aux_insert(node_t **root, int value)
{
    if (*root == NULL) {
        *root = create_node(value);
        return;
    }

    if (value < (*root)->key) {
        aux_insert(&((*root)->left), value);
    } else if (value > (*root)->key) {
        aux_insert(&((*root)->right), value);
    } else {
        return; // No permitir claves duplicadas
    }

    // Actualizar la altura del nodo actual
    (*root)->height = height(*root);

    // Calcular el factor de equilibrio del nodo actual
    int fe = balance_factor(*root);

    // Realizar rotaciones según los casos de desequilibrio
    // (izquierda-izquierda, izquierda-derecha, derecha-derecha, derecha-izquierda)
    if (fe > 1 && value > (*root)->right->key) {
        left_rotation(root);
    }

    if (fe < -1 && value < (*root)->left->key) {
        right_rotation(root);
    }

    if (fe > 1 && value < (*root)->right->key) {
        right_rotation(&((*root)->right));
        left_rotation(root);
    }

    if (fe < -1 && value > (*root)->left->key) {
        left_rotation(&((*root)->left));
        right_rotation(root);
    }
}

int height(node_t *node)
{
    if(node == NULL){
        return -1;
    }
    int left = height(node->left);
    int right = height(node->right);
    return 1 + (left > right ? left : right);
}

int balance_factor( node_t *node)
{
    return (node->right == NULL ? -1 : node->right->height) - (node->left == NULL ? -1 : node->left->height);
}

void right_rotation(node_t **root)
{
    node_t *y = *root;
    node_t *x = y->left;
    node_t *t2 = x->right;

    x->right = y;
    y->left = t2;
    *root = x;

    x->height = height(x);
    y->height = height(y);
    x->fe = balance_factor(x);
    y->fe = balance_factor(y);
}

void left_rotation(node_t **root)
{
    node_t *x = *root;
    node_t *y =x->right;
    node_t *t2 = y->left;

    y->left = x;
    x->right = t2;
    *root = y;

    y->height = height(y);
    x->height = height(x);
    y->fe = balance_factor(y);
    x->fe = balance_factor(x);
}

void free_tree(node_t* root) 
{
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

queue_t* createQueue()
{
    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
    queue->front = queue->rear = NULL;
    return queue;
}

int is_empty(queue_t *queue)
{
    if(queue->front == NULL){
        return 1;
    }
    return 0;
}

queue_node_t* createQueueNode(node_t* treeNode)
{
    queue_node_t *node = (queue_node_t*)malloc(sizeof(queue_node_t));
    node->avl_node = treeNode;
    node->next = NULL;
    return node;
}

void enqueue(queue_t* queue, node_t* treeNode)
{
    queue_node_t *new = createQueueNode(treeNode);

    if(is_empty(queue) == 1){
        queue->front = queue->rear = new;
        return;
    }
    queue->rear->next = new;
    queue->rear = new;
}
