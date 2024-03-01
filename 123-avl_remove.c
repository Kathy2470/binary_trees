#include <stdlib.h>
#include "binary_trees.h"

/**
 * find_successor - Find the in-order successor of a given node
 * @node: Pointer to the node
 *
 * Return: Pointer to the in-order successor, or NULL if node has no right child
 */
avl_t *find_successor(avl_t *node)
{
	while (node->left != NULL)
		node = node->left;
	return (node);
}

/**
 * avl_remove - Removes a node with a specific value from an AVL tree
 * @root: Pointer to the root node of the AVL tree
 * @value: Value to remove from the AVL tree
 *
 * Return: Pointer to the new root node of the tree after removing the value
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *temp = NULL;

	if (root == NULL)
		return (NULL);

	if (value < root->n)
		root->left = avl_remove(root->left, value);
	else if (value > root->n)
		root->right = avl_remove(root->right, value);
	else
	{
		if (root->left == NULL || root->right == NULL)
		{
			temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			temp = find_successor(root->right);
			root->n = temp->n;
			root->right = avl_remove(root->right, temp->n);
		}
	}

	if (root == NULL)
		return (NULL);

	root->height = 1 + MAX(binary_tree_height(root->left),
			       binary_tree_height(root->right));

	int balance = binary_tree_balance(root);

	if (balance > 1 && binary_tree_balance(root->left) >= 0)
		return (binary_tree_rotate_right(root));
	if (balance > 1 && binary_tree_balance(root->left) < 0)
	{
		root->left = binary_tree_rotate_left(root->left);
		return (binary_tree_rotate_right(root));
	}
	if (balance < -1 && binary_tree_balance(root->right) <= 0)
		return (binary_tree_rotate_left(root));
	if (balance < -1 && binary_tree_balance(root->right) > 0)
	{
		root->right = binary_tree_rotate_right(root->right);
		return (binary_tree_rotate_left(root));
	}

	return (root);
}
