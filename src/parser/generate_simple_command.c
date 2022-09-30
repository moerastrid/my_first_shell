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

int	generate_simple_command(t_cmd *cmd, char **argv)
{
	t_simple	*new_simple;
	char		*myexec;
	char		*temp;
	int			i;

	new_simple = (t_simple *)malloc(sizeof(t_simple));
	if (!new_simple)
		return (-1);
	new_simple->argv = NULL;
	new_simple->bin = NULL;
	new_simple->next = NULL;
	new_simple->argv = argv;
	if (access(argv[0], X_OK) == 0)
		new_simple->bin = argv[0];
	i = 0;
	while (cmd->paths[i] != NULL)
	{
		myexec = NULL;
		temp = ft_strjoin(cmd->paths[i], "/");
		if (!temp)
			return (-1);
		myexec = ft_strjoin(temp, argv[0]);
		if (!myexec)
			return (-1);
		free (temp);
		if (access(myexec, X_OK) == 0)
		{
			new_simple->bin = myexec;
			printf("acces ok!\n");
			break ;
		}
		free (myexec);
		i++;
	}
	simpleadd_back(&cmd->simples, new_simple);
	return (0);
}
