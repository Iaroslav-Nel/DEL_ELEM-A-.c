#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node {
    Data val;            
    struct Node * left;  
    struct Node * right;
    struct Node * parent;
    char state;
};

struct Node * tree_add(struct Node * tree, Data x, struct Node * par, char st) {
	if (tree == NULL) {
		tree = (struct Node*)malloc(sizeof(struct Node));
		tree->val = x;
		tree->left = NULL;
		tree->right = NULL;
        tree->parent = par;
        tree->state = st;
		return tree;
	}
	if (x < tree->val) {
		tree->left = tree_add(tree->left, x, tree, 'l');
		return tree;
	} 
	if (x > tree->val) {
		tree->right = tree_add(tree->right, x, tree, 'r');
		return tree;
	}	
	return tree;	
}

void tree_print(struct Node * tree) {
	if (tree != NULL) {
		tree_print(tree->left);
		printf("%d ", (int)tree->val);
		tree_print(tree->right);
    }
}

void tree_destroy(struct Node * tree) {
	if (tree != NULL) {
		tree_destroy(tree->left);
		tree_destroy(tree->right);
		free(tree);
	}
}

struct Node * FOUND = NULL;

void search_for_adress(struct Node * tree, Data element) {
	if (tree != NULL) {
        if (tree->val == element) {
            FOUND = tree;
        } else {
		    search_for_adress(tree->left, element);
            search_for_adress(tree->right, element);
        }
    }
}

void tree_delete_element(struct Node * tree, Data element, struct Node ** root) {
    search_for_adress(tree, element);
    if ((FOUND->left == NULL) && (FOUND->right == NULL)) {
        if (FOUND->parent == NULL) {
            free(FOUND);
            *root = NULL;
            return;
        }
        if (FOUND->state == 'l') {
            (FOUND->parent)->left = NULL;
        } else {
            (FOUND->parent)->right = NULL;
        }
        free(FOUND);
        return;
    }
    if (FOUND->left == NULL) {
        if (FOUND->parent == NULL) {
            *root = FOUND->right;
            FOUND->right->parent = NULL;
            FOUND->right->state = 'm';
            free(FOUND);
            return;
        }
        if (FOUND->state == 'l') {
            FOUND->parent->left = FOUND->right;
            FOUND->right->parent = FOUND->parent;
            FOUND->right->state = 'l';
        } else {
            FOUND->parent->right = FOUND->right;
            FOUND->right->parent = FOUND->parent;
        }
        free(FOUND);
        return;
    }
    if (FOUND->right == NULL) {
        if (FOUND->parent == NULL) {
            *root = FOUND->right;
            FOUND->left->parent = NULL;
            FOUND->left->state = 'm';
            free(FOUND);
            return;
        }
        if (FOUND->state == 'l') {
            FOUND->parent->left = FOUND->left;
            FOUND->left->parent = FOUND->parent;
        } else {
            FOUND->parent->right = FOUND->right;
            FOUND->left->parent = FOUND->parent;
            FOUND->left->state = 'r';
        }
        free(FOUND);
        return;
    }
    if ((FOUND->left != NULL) && (FOUND->right != NULL)) {
        struct Node * swap = FOUND->right;
        int counter = 0;
        while (swap->left != NULL) {
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
        } else  if (FOUND->state == 'r') {
            FOUND->parent->right = swap;
        } else {
            *root = swap;
        }
        free(FOUND);
        return;
    }
    printf("func tree_delete_element ERROR!\n");
}

int main() {
	struct Node * tree = NULL;
	int a = 0;
	scanf("%d", &a);
	while (a != 0) {
		tree = tree_add(tree, a, NULL, 'm');
		scanf("%d", &a);
	}
	tree_print(tree);
    Data b = 0;
    putchar('\n');
    scanf("%d", &b);
    tree_delete_element(tree, b, &tree);
    tree_print(tree);
//    search_for_adress(tree, b);
//    printf("%d", FOUND->val);
    tree_destroy(tree);
	return 0;
}
