/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:22 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 17:37:45 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_simple(t_simple *simple)
{
	int	i;

	i = 0;
	while (i < simple->argc)
	{
		if (simple->argv[i])
			free(simple->argv[i]);
		simple->argv[i] = NULL;
		i++;
	}
	if (simple->argv)
		free(simple->argv);
	if (simple->bin)
		free(simple->bin);
	simple->argv = NULL;
	simple->bin = NULL;
}

void	free_simples(t_simple *simples)
{
	t_simple	*next;

	while (simples != NULL)
	{
		next = simples->next;
		free_simple(simples);
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

t_simple	*simple_tail(t_simple *simple)
{
	if (!simple)
		return (simple);
	if (!simple->next)
		return (simple);
	while(simple->next != NULL)
		simple = simple->next;
	return (simple);
}
