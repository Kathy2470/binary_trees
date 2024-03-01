#include "binary_trees.h"

/**
 * avl_insert_node - Inserts a value into an AVL tree node
 * @parent: Pointer to the parent node
 * @value: Value to store in the new node
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
avl_t *avl_insert_node(avl_t *parent, int value)
{
	avl_t *node = NULL;

	if (parent == NULL)
		return (NULL);

	if (value < parent->n)
	{
		if (parent->left == NULL)
		{
			node = binary_tree_node(parent, value);
			if (node == NULL)
				return (NULL);
			parent->left = node;
		}
		else
		{
			node = avl_insert_node(parent->left, value);
			if (node == NULL)
				return (NULL);
		}
	}
	else if (value > parent->n)
	{
		if (parent->right == NULL)
		{
			node = binary_tree_node(parent, value);
			if (node == NULL)
				return (NULL);
			parent->right = node;
		}
		else
		{
			node = avl_insert_node(parent->right, value);
			if (node == NULL)
				return (NULL);
		}
	}

	return (node);
}

/**
 * avl_insert - Inserts a value into an AVL tree
 * @tree: Pointer to the root node of the AVL tree
 * @value: Value to store in the new node
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *node = NULL;

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}

	node = avl_insert_node(*tree, value);
	if (node == NULL)
		return (NULL);

	while (node->parent != NULL)
	{
		*tree = node->parent;
		node = node->parent;
	}

	return (*tree);
}
