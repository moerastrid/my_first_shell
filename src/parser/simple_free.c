/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:30:01 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:30:02 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_argv(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (argv[i])
			free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	free(argv);
}

static void	free_simple(t_simple *simple)
{
	if (simple->argv)
		free_argv(simple->argv, simple->argc);
	if (simple->bin)
		free(simple->bin);
	free_str_list(simple->infiles);
	free_str_list(simple->outfiles);
	simple->argv = NULL;
	simple->bin = NULL;
	free(simple);
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
