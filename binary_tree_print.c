#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

/**
 * _binary_tree_print - Recursively builds tree representation
 * @tree: Tree to print
 * @offset: Current offset
 * @depth: Current depth
 * @s: Array of lines
 * Return: Depth of printed tree
 */
static size_t _binary_tree_print(const binary_tree_t *tree, int offset,
				 int depth, char **s)
{
	char b[6];
	int width, is_left, i;
	size_t left_depth, right_depth;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left_depth = _binary_tree_print(tree->left, offset, depth + 1, s);
	right_depth = _binary_tree_print(tree->right, offset + left_depth
					+ width, depth + 1, s);
	for (i = 0; i < width; i++)
		s[depth][offset + left_depth + i] = b[i];
	if (depth && is_left)
	{
		for (i = 0; (size_t)i < width + right_depth; i++)
			s[depth - 1][offset + left_depth + width / 2 + i] = '-';
		s[depth - 1][offset + left_depth + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; (size_t)i < left_depth + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left_depth + width / 2] = '.';
	}
	return (left_depth + width + right_depth);
}

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height, i, j;

	if (!tree)
		return;
	height = 128;
	s = malloc(sizeof(*s) * height);
	if (!s)
		return;
	for (i = 0; i < height; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 254);
		s[i][254] = '\0';
	}
	_binary_tree_print(tree, 0, 0, s);
	for (i = 0; i < height; i++)
	{
		for (j = 253; j > 0; j--)
		{
			if (s[i][j] != ' ')
				break;
		}
		if (j == 0)
		{
			free(s[i]);
			break;
		}
		s[i][j + 1] = '\0';
		printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}
