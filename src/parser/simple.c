/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:22 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 17:45:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple	*new_simple(int argc, char **argv)
{
	t_simple	*new_simple;

	new_simple = (t_simple *)ft_calloc(1, sizeof(t_simple));
	if (!new_simple)
		return (NULL);
	new_simple->bin = NULL;
	new_simple->next = NULL;
	new_simple->infiles = NULL;
	new_simple->outfiles = NULL;
	new_simple->argc = argc;
	new_simple->argv = argv;
	return (new_simple);
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

t_simple	*simple_tail(t_simple *simple)
{
	if (!simple)
		return (simple);
	while (simple->next != NULL)
		simple = simple->next;
	return (simple);
}

int	count_simples(t_cmd *cmd)
{
	int			cmd_count;
	t_simple	*simples;

	cmd_count = 0;
	simples = cmd->simples;
	while (simples != NULL)
	{
		cmd_count++;
		simples = simples->next;
	}
	return (cmd_count);
}
