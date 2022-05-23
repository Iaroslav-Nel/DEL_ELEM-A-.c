#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int Data;                   // создаем тип данных Data которая будет хранить целые значения

struct Node 
{
    Data val;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    char state;
};

struct Node* tree_add(struct Node* tree, Data x, struct Node* par, char st)      // функция добавления элемента в дерево
{
    if (tree == NULL) 
    {
        tree = (struct Node*)malloc(sizeof(struct Node));               // динамический массив структур
        tree->val = x;                  // сюда будут помещаться значения из входного потока
        tree->left = NULL;              // 
        tree->right = NULL;             // 
        tree->parent = par;
        tree->state = st;
        return tree;
    }
    if (x < tree->val)                  // если число меньше предыдущего значения то 
    {
        tree->left = tree_add(tree->left, x, tree, 'l');
        return tree;
    }
    if (x > tree->val)                  // если число больше 
    {
        tree->right = tree_add(tree->right, x, tree, 'r');
        return tree;
    }
    return tree;
}

void tree_print(struct Node* tree)                  // в этой функции происходит рекурсия и элементы дерева будут печататься от наименьшего к большему 
{
    if (tree != NULL) 
    {
        tree_print(tree->left);
        printf("%d ", (int)tree->val);
        tree_print(tree->right);
    }
}

void tree_destroy(struct Node* tree)            //функция которая освобождает память в динамическом массиве tree 
{
    if (tree != NULL) 
    {
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);                             // освобождение памяти
    }
}

struct Node* FOUND = NULL;

void search_for_adress(struct Node* tree, Data element) 
{
    if (tree != NULL)                           // будем перебирать все дерево до тех пор пока не найдем элемент                                       
    {
        if (tree->val == element)               // если значение в дереве равно удаляемому элементу то...
        {
            FOUND = tree;                       //найденный элемент
        }
        else 
        {
            search_for_adress(tree->left, element);
            search_for_adress(tree->right, element);
        }
    }
}

void tree_delete_element(struct Node* tree, Data element, struct Node** root)           // функция для удаления элемента из дерева
{                                                                                       
    search_for_adress(tree, element);                           // поиск адреса удаляемого элемента из дерева
    if ((FOUND->left == NULL) && (FOUND->right == NULL))
    {
        if (FOUND->parent == NULL) 
        {
            free(FOUND);
            *root = NULL;
            return;
        }
        if (FOUND->state == 'l')            // если слева найден
        {
            (FOUND->parent)->left = NULL;
        }
        else                                // найден справа
        {
            (FOUND->parent)->right = NULL;          
        }
        free(FOUND);
        return;
    }
    if (FOUND->left == NULL) 
    {
        if (FOUND->parent == NULL) 
        {
            *root = FOUND->right;
            FOUND->right->parent = NULL;
            FOUND->right->state = 'm';
            free(FOUND);
            return;
        }
        if (FOUND->state == 'l') 
        {
            FOUND->parent->left = FOUND->right;
            FOUND->right->parent = FOUND->parent;
            FOUND->right->state = 'l';
        }
        else 
        {
            FOUND->parent->right = FOUND->right;
            FOUND->right->parent = FOUND->parent;
        }
        free(FOUND);
        return;
    }
    if (FOUND->right == NULL) 
    {
        if (FOUND->parent == NULL) 
        {
            *root = FOUND->right;
            FOUND->left->parent = NULL;
            FOUND->left->state = 'm'; 
            free(FOUND);
            return;
        }
        if (FOUND->state == 'l') 
        {
            FOUND->parent->left = FOUND->left;
            FOUND->left->parent = FOUND->parent;
        }
        else 
        {
            FOUND->parent->right = FOUND->right;
            FOUND->left->parent = FOUND->parent;
            FOUND->left->state = 'r';
        }
        free(FOUND);
        return;
    }
    if ((FOUND->left != NULL) && (FOUND->right != NULL)) 
    {
        struct Node* swap = FOUND->right;
        int counter = 0;
        while (swap->left != NULL) 
        {
            swap = swap->left;
            ++counter;
        }
        swap->left = FOUND->left;
        if (counter != 0) {
            swap->right = FOUND->right;
            swap->parent->left = NULL;
        }
        FOUND->left->parent = swap;
        FOUND->right->parent = swap;
        swap->state = FOUND->state;
        swap->parent = FOUND->parent;
        if (FOUND->state == 'l') {
            FOUND->parent->left = swap;
        }
        else  if (FOUND->state == 'r') {
            FOUND->parent->right = swap;
        }
        else {
            *root = swap;
        }
        free(FOUND);
        return;
    }
    printf("func tree_delete_element ERROR!\n");        // если ни одно из условий не подошло
}

int main() 
{
    struct Node* tree = NULL;                       // tree является структурой указателем на структуру
    int a = 0;
    scanf("%d", &a);                                // входной поток ... 
    while (a != 0) 
    {
        tree = tree_add(tree, a, NULL, 'm');        // функция которая добавляет числа в дерево   ""
        scanf("%d", &a);                            // вводим числа до тех пор пока мы не введем ноль
    }                                               // эти числа будут последовательно выведены на экран
    tree_print(tree);                               // эта функция будет печатать дерево чисел которое будет выведено от наименьшего к большему ex: при введении 1 5 4 3 ---> 1 3 4 5 
    Data b = 0;
    putchar('\n');
    scanf("%d", &b);                                // ввести элемент который мы хотим удалить      ex: введем 3 и она удалится из дерева ex: 1 3 4 5 ---> 1 4 5
    tree_delete_element(tree, b, &tree);            // эта функция удаляет из нашего созданного последовательного дерева элемент...
    tree_print(tree);                               // напечатать дерево
    //    search_for_adress(tree, b);
    //    printf("%d", FOUND->val);
    tree_destroy(tree);                             // очищение выделения динамической памяти 
    return 0;
}
