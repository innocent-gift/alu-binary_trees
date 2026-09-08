#include <stdlib.h>
#include "binary_trees.h"

int main(void)
{
    binary_tree_t *root;

    root = binary_tree_node(NULL, 98);
    root->left = binary_tree_node(root, 12);
    root->right = binary_tree_node(root, 402);

    binary_tree_print(root);
    return (0);
}
