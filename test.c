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

void insert_line(text_t *txt, int index, char * new_line) 
{
	text_t *tmp_node = txt;
	int finished;
	int count = index;
	if (txt->left == NULL)
	{
		txt->left = (text_t *) create_object(new_line); 
      		txt->key  = 1;
      		txt->right  = NULL;
		txt->parent = NULL;
		txt->height = 0;
	}
	else if (index > (tmp_node->key))
	{
		append_line(txt, new_line);
	}	
	else
	{
		while(tmp_node->right != NULL)
        	{
        		(tmp_node->key)++;
			if (count <= tmp_node->left->key)
			{
				tmp_node = tmp_node->left;
			}
			else
			{
				count -= tmp_node->left->key;
				tmp_node = tmp_node->right;
			}
		}

	        text_t *old_leaf, *new_leaf;
        	old_leaf = get_node();
        	new_leaf = get_node();
        	old_leaf->left = tmp_node->left;
        	old_leaf->key = 1;
        	old_leaf->right  = NULL;
        	old_leaf->parent = tmp_node;
        	old_leaf->height = 0;

        	new_leaf->left = (text_t *) create_object(new_line);
        	new_leaf->key = 1;
        	new_leaf->right  = NULL;
        	new_leaf->parent = tmp_node;
        	new_leaf->height = 0;
        	tmp_node->right = old_leaf;
        	tmp_node->left = new_leaf;
		(tmp_node->key)++; 
		tmp_node->height = 0;
		  
		finished = 0;
		while(!finished && tmp_node!=NULL)
		{
			int tmp_height, old_height;
			old_height = tmp_node->height;
			if (tmp_node->left->height - tmp_node->right->height == 2)
			{ 
				if (tmp_node->left->left->height - tmp_node->right->height == 1)
				{ 
					right_rotation(tmp_node);
					tmp_node->right->height = tmp_node->right->left->height + 1;
					tmp_node->height = tmp_node->right->height + 1;
					tmp_node->right->key = tmp_node->right->left->key + tmp_node->right->right->key;
					tmp_node->key = tmp_node->left->key + tmp_node->right->key;
				}
				else
				{ 
					left_rotation(tmp_node->left);
					right_rotation(tmp_node);
					tmp_height = tmp_node->left->left->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;
					tmp_node->left->key = tmp_node->left->left->key + tmp_node->left->right->key;
					tmp_node->right->key = tmp_node->right->left->key + tmp_node->right->right->key;
                                        tmp_node->key = tmp_node->left->key + tmp_node->right->key;
				}
			}
			else if (tmp_node->left->height - tmp_node->right->height == -2)
			{ 
				if( tmp_node->right->right->height - tmp_node->left->height == 1)
				{ 
					left_rotation(tmp_node);
					tmp_node->left->height = tmp_node->left->right->height + 1;
					tmp_node->height = tmp_node->left->height + 1;
					tmp_node->left->key = tmp_node->left->left->key + tmp_node->left->right->key;
                                        tmp_node->key = tmp_node->left->key + tmp_node->right->key;
				}
				else
				{ 
					right_rotation(tmp_node->right);
					left_rotation(tmp_node);
					tmp_height = tmp_node->right->right->height;
					tmp_node->left->height = tmp_height + 1;
					tmp_node->right->height = tmp_height + 1;
					tmp_node->height = tmp_height + 2;
					tmp_node->right->key = tmp_node->right->left->key + tmp_node->right->right->key;
					tmp_node->left->key = tmp_node->left->left->key + tmp_node->left->right->key;
                                        tmp_node->key = tmp_node->left->key + tmp_node->right->key;
				}
			}
      			else 
			{ 
				if(tmp_node->left->height > tmp_node->right->height)
				{
					tmp_node->height = tmp_node->left->height + 1;
				}
				else
				{
					tmp_node->height = tmp_node->right->height + 1;
				}
			}
			if (tmp_node->height == old_height)
			{
				finished = 1;
			}
			tmp_node = tmp_node->parent;
		}
	}

}