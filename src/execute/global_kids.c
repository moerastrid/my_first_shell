#include "../../minishell.h"

void	free_children(t_children *root)
{
	t_children	*next;
	while(root != NULL)
	{
		next = root->next;
		free(root);
		root = next;
	}
}

t_children	*new_child(pid_t id)
{
	t_children	*new;

	new = ft_calloc(1, sizeof(t_children));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->next = NULL;
	return (new);
}

void	child_add_back(t_children *root, t_children *new)
{
	if (root == NULL)
		return ;
	while (root->next != NULL)
	{
		root = root->next;
	}
	root->next = new;
}

void	kill_children(t_children *kids)
{
	while (kids != NULL)
	{
		printf("%d\n", kids->id);
		kill(kids->id, SIGKILL);
		kids = kids->next;
	}
}