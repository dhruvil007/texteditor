#include <stdio.h>
#include <stdlib.h>

typedef int key_t;
typedef char object_t;

typedef struct txt_n_t
{
	int key;
	char str[100];
	struct text_node_t *left;
	struct text_node_t *right;
} text_node_t;

#define BLOCKSIZE 256

text_node_t *currentblock = NULL;
int size_left;
text_node_t *free_list = NULL;
int nodes_taken = 0;
int nodes_returned = 0;

text_node_t get_node()
{
	text_node_t *tmp_node;
	nodes_taken += 1;
	if (free_list != NULL)
	{
		tmp = free_list;
		free_list = free_list -> right;
	}
	else
	{
		if (currentblock == NULL || size_left ==0)
			{
				currentblock = (text_node_t *) malloc(BLOCKSIZE * sizeof(text_node_t));
				size_left = BLOCKSIZE;
			}
		tmp = currentblock++;
		size_left -= 1;
	}
	return tmp_node;
}

text_node_t *return_node(text_node_t *node)
{
	node -> right = free_list;
	free_list = node;
	nodes_returned += 1;
}

text_node_t *create_text()
{
	text_node_t *tmp_node;
	tmp_node = get_node();
	tmp_node -> left = NULL;
	return tmp_node;
}

int length_text(text_node_t *txt)
{
	if (txt == NULL)
		return 0;
	else
		return 1 + length_text(txt -> left) + length_text(txt -> right);
}

char *get_line(text_node_t *txt, int index)
{
	if (txt -> left == NULL || (txt -> right == NULL && txt -> key != index))
		return NULL;
	else if (txt -> right == NULL && txt -> key == index)
		return ((object_t *) txt -> left);
	else
	{
	if (index < txt -> key)
		return get_line(txt -> left, index);
	else
		return get_line(txt -> right, index);
	}
}