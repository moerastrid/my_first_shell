#include "parser.h"

static void	free_simple(t_simple *simple)
{
	int	i;

	i = 0;
	while (i < simple->argc)
	{
		free(simple->argv[i]);
		i++;
	}
	free(simple->argv);
	//free(simple->bin);
	simple->argv = NULL;
	simple->bin = NULL;
}

void	free_simples(t_simple *simples)
{
	t_simple	*next;

	while (simples != NULL)
	{
		free_simple(simples);
		next = simples->next;
		free(simples);
		simples = next;
	}
}

void	simple_add_back(t_simple **lst, t_simple *new_elem)
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

	new_simple = (t_simple *)ft_calloc(1, sizeof(t_simple));
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

	if (!simple || !simple->argv || !cmd)
		return (-2);
	if (access(simple->argv[0], X_OK) == 0)
		simple->bin = simple->argv[0];
	i = 0;
	while (cmd->paths && cmd->paths[i])
	{
		myexec = NULL;
		temp = ft_strjoin(cmd->paths[i++], "/");
		if (!temp)
			return (-1);
		myexec = ft_strjoin(temp, simple->argv[0]);
		free(temp);
		if (!myexec)
			return (-1);
		if (access(myexec, X_OK) == 0)
		{
			simple->bin = myexec;
			break ;
		}
		free (myexec);
	}
	return (0);
}
