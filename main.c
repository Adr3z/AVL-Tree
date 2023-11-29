/*

Tarea 10: Árboles Balanceados AVL

Estructuras de Datos II

Fecha de publicación: Martes 21 de noviembre de 2023
Fecha de entrega: Martes 28 de noviembre de 2023

Nombre del alumno: Lara López Fryda Renata

Nombre de usuario en omegaUp: FrydaLara

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
    int level;
    struct queue_node *next;
}queue_node_t;

typedef struct queue{
    queue_node_t *front;
    queue_node_t *rear;
}queue_t;

//Main functions
void insert_node( node_t **root);
void erase_node( node_t **root);
void print_height(node_t *root);
void print_by_level(node_t *root);

//avl functions
node_t* create_node( int key);
int max( int h1, int h2);
int balance_factor( node_t *node);
void right_rotation(node_t **root);
void left_rotation(node_t **root);
void aux_insert(node_t **root, int value);
void aux_erase(node_t **root, int value);
void make_balance( node_t **root);
node_t *min(node_t *node);
void free_tree(node_t* root);

//bfs functions
queue_t *createQueue();
void enqueue(queue_t *queue, node_t *avl_node, int level);
queue_node_t *dequeue(queue_t *queue);
queue_node_t *createQueueNode(node_t *avl_node, int level);
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
    //printf("Inserting node with value %d\n", value);
#endif
    // TODO: insert node with the specified value
    aux_insert(&(*root), value);
}

void erase_node( node_t **root)
{
    int value;
    scanf("%d", &value);
#ifdef DEBUG
    //printf("Erasing node with value %d\n", value);
#endif
    aux_erase(&(*root), value);
}

void print_height(node_t *root)
{
#ifdef DEBUG
    //printf("Printing the tree's height\n");
#endif
    if (root == NULL) {
        printf("-1");
    } else {
        printf("%d\n", root->height);
    }
}

void print_by_level(node_t *root)
{
#ifdef DEBUG
#endif
     if (root == NULL) {
        printf("\n");
        return;
    }

    queue_t *queue = createQueue();
    enqueue(queue, root, 0);

    int current_level = -1;

    while (!is_empty(queue)) {
        queue_node_t *current_node = dequeue(queue);

        printf("%d ", current_node->avl_node->key);

        if (current_node->avl_node->left != NULL) {
            enqueue(queue, current_node->avl_node->left, current_level + 1);
        }

        if (current_node->avl_node->right != NULL) {
            enqueue(queue, current_node->avl_node->right, current_level + 1);
        }

        free(current_node);
    }

    free(queue);
    printf("\n");
}

node_t* create_node( int key)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    new_node->fe = new_node->height = 0;
    return new_node;
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
    
    (*root)->height =  1 + max((*root)->right == NULL ? -1 : (*root)->right->height, (*root)->left == NULL ? -1 : (*root)->left->height);
    make_balance(root);
}

void aux_erase(node_t **root, int value)
{
    if( *root == NULL){
        return;
    }

    if((*root)->key == value) {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            //Caso 1: El nodo es una hoja
            free(*root);
            *root = NULL;
        } else if ((*root)->left == NULL) {
            //Caso 2: hijo derecho
            node_t *aux = *root;
            *root = (*root)->right;
            free(aux);
        } else if ((*root)->right == NULL) {
            //Caso 2: hijo izquierdo
            node_t *aux = *root;
            *root = (*root)->left;
            free(aux);
        } else {
            // Caso 3: El nodo tiene 2 hijos
            node_t* sucesor = min((*root)->right);
            (*root)->key = sucesor->key;
            aux_erase(&((*root)->right), sucesor->key);
        }
    }

    if (*root == NULL) {
        return;
    }

    if(value < (*root)->key){
        aux_erase(&((*root)->left), value);
    } else if (value > (*root)->key) {
        aux_erase(&((*root)->right), value);
    }

    if (*root) {
        (*root)->height = 1 + max((*root)->right == NULL ? -1 : (*root)->right->height, (*root)->left == NULL ? -1 : (*root)->left->height);
    }
    make_balance(root);
}

void make_balance( node_t **root)
{
    //Calcular el factor de equilibrio
    int fe = balance_factor(*root);

    //Realizar rotaciones 
        if (fe > 1) {
        if (balance_factor((*root)->right) < 0) {
            // Caso de rotación derecha-izquierda
            right_rotation(&((*root)->right));
        }
        // Caso de rotación izquierda
        left_rotation(root);
    } else if (fe < -1) {
        if (balance_factor((*root)->left) > 0) {
            // Caso de rotación izquierda-derecha
            left_rotation(&((*root)->left));
        }
        // Caso de rotación derecha
        right_rotation(root);
    }
}

node_t *min(node_t *node)
{
     while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

int max( int h1, int h2)
{
    return (h1 > h2) ? h1 : h2;
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

    y->height = 1 + max(y->right == NULL ? -1 : y->right->height, y->left == NULL ? -1 : y->left->height);
    x->height = 1 + max(x->right == NULL ? -1 : x->right->height, x->left == NULL ? -1 : x->left->height);
    y->fe = balance_factor(y);
    x->fe = balance_factor(x);
}

void left_rotation(node_t **root)
{
    node_t *x = *root;
    node_t *y =x->right;
    node_t *t2 = y->left;

    y->left = x;
    x->right = t2;
    *root = y;

    x->height = 1 + max(x->right == NULL ? -1 : x->right->height, x->left == NULL ? -1 : x->left->height);
    y->height = 1 + max(y->right == NULL ? -1 : y->right->height, y->left == NULL ? -1 : y->left->height);
    x->fe = balance_factor(x);
    y->fe = balance_factor(y);
}

void free_tree(node_t* root) 
{
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

queue_t *createQueue() 
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, node_t *avl_node, int level) 
{
    queue_node_t *new_node = createQueueNode(avl_node, level);

    if (is_empty(queue)) {
        queue->front = queue->rear = new_node;
        return;
    }

    queue->rear->next = new_node;
    queue->rear = new_node;
}

queue_node_t *dequeue(queue_t *queue)
{
    if (is_empty(queue)) {
        return NULL;
    }

    queue_node_t *front_node = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return front_node;
}

queue_node_t *createQueueNode(node_t *avl_node, int level) 
{
    queue_node_t *node = (queue_node_t *)malloc(sizeof(queue_node_t));
    node->avl_node = avl_node;
    node->level = level;
    node->next = NULL;
    return node;
}

int is_empty(queue_t *queue) 
{
    return (queue->front == NULL);
}
