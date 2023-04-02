#include "tree_soft.h"
#include "diff.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "dotter.h"

static void node_print(struct Node* node);

struct Node* create_node(int type, double value, struct Node* left, struct Node* right)
{
    struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));

    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

void push_node(struct Node* node, int type, double value)
{
    node->type = type;
    node->value = value;
}

void delete_tree(struct Node* node)
{
    if(node == nullptr)
        return;

    delete_tree(node->left);
    delete_tree(node->right);

    free(node);
}

void tree_print(struct Node* tree)
{
    if(tree == nullptr)
        return;

    graph_start();
    graph_add_root(tree);

    node_print(tree);

    graph_end();
}

static void node_print(struct Node* node)
{
    if(node == nullptr)
        return;

    node_print(node->left);
    node_print(node->right);

    if(node->type == NUMBER)
        graph_add_dot(node, node->value, node->type, node->left, node->right, "#FFD0D0");
    else if(node->type == ADD || node->type == SUB || node->type == MUL || node->type == DIV)
        graph_add_dot(node, node->value, node->type, node->left, node->right, "#D0FFD0");
    else if(node->type == VAR)
        graph_add_dot(node, node->value, node->type, node->left, node->right, "#D0D0FF");
    else
        graph_add_dot(node, node->value, node->type, node->left, node->right, "#FF0000");

    if(node->left != nullptr)
        graph_add_arrow(node, node->left, "#0000FF");

    if(node->right != nullptr)
        graph_add_arrow(node, node->right, "#FF0000");
}

void tree_print_inorder(struct Node* tree)
{
    if(tree == nullptr)
        return;

    printf("( ");

    tree_print_inorder(tree->left);

    if(tree->type == 0)
        printf("%lf ", tree->value);
    else
    {
        switch((int)tree->value)
        {
            case 1:   printf("+ "); break;
            case 2:   printf("- "); break;
            case 3:   printf("* "); break;
            case 4:   printf("/ "); break;
            default:  printf("bebra\n"); break;
        }
    }

    tree_print_inorder(tree->right);

    printf(") ");
}

struct Node* copy_node(struct Node* node)
{
    if(node == nullptr)
        return nullptr;

    return create_node(node->type, node->value, copy_node(node->left), copy_node(node->right));
}
