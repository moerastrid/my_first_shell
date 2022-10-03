#include "../../minishell.h"

t_str_list *str_list_new(char *str, int append_mode)
{
	t_str_list *new;

	new = malloc(sizeof(t_str_list));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->append_mode = append_mode;
	new->next = NULL;
	return (new);
}

void str_list_add_back(t_str_list *root, t_str_list *new)
{
	if (root == NULL)
		return ;
	while (root->next != NULL)
		root = root->next;
	root->next = new;
}

void free_str_list(t_str_list *root)
{
	t_str_list	*temp;
	while(root != NULL)
	{
		free(root->str);
		temp = root->next;
		free(root);
		root = temp;
	}
	root = NULL;
}