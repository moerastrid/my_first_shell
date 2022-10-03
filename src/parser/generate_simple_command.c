#include "../../minishell.h"

void	simpleadd_back(t_simple **lst, t_simple *new_elem)
{
	t_simple	*tmp;

	if (!lst)
		return ;
	tmp = lst[0];
	if (tmp == NULL)
	{
		lst[0] = new_elem;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_elem;
}

t_simple	*new_simple(int argc, char **argv)
{
	t_simple	*new_simple;

	new_simple = (t_simple *)malloc(sizeof(t_simple));
	if (!new_simple)
		return (NULL);
	new_simple->bin = NULL;
	new_simple->next = NULL;
	new_simple->argc = argc;
	new_simple->argv = argv;
	return (new_simple);
}

int	set_bin(t_cmd *cmd, t_simple *simple)
{
	char		*myexec;
	char		*temp;
	int			i;

	if (access(simple->argv[0], X_OK) == 0)
		simple->bin = simple->argv[0];
	i = 0;
	while (cmd->paths[i] != NULL)
	{
		myexec = NULL;
		temp = ft_strjoin(cmd->paths[i], "/");
		if (!temp)
			return (-1);
		myexec = ft_strjoin(temp, simple->argv[0]);
		if (!myexec)
			return (-1);
		free (temp);
		if (access(myexec, X_OK) == 0)
		{
			simple->bin = myexec;
			break ;
		}
		free (myexec);
		i++;
	}
	return (0);
}
