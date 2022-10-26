/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simple_argv_builder.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:57 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:55:47 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	simple_add_outfile(t_simple *simple, char *fname, int append)
{
	if (simple->outfiles == NULL)
		simple->outfiles = str_list_new(fname, append);
	else
		str_list_add_back(simple->outfiles, str_list_new(fname, append));
	return (0);
}

int	simple_add_infile(t_simple *simple, char *fname, int append)
{
	if (simple->infiles == NULL)
		simple->infiles = str_list_new(fname, append);
	else
		str_list_add_back(simple->infiles, str_list_new(fname, append));
	return (0);
}

int	add_arg(t_cmd *cmd, char *arg)
{
	char		**argv;
	t_simple	*tail;
	int			i;

	if (arg == NULL)
		return (-1);
	tail = simple_tail(cmd->simples);
	argv = ft_calloc(sizeof(char **), (tail->argc + 2));
	if (argv == NULL)
		return (-1);
	i = 0;
	while (i < tail->argc)
	{
		argv[i] = tail->argv[i];
		i++;
	}
	if (tail->argv)
		free(tail->argv);
	argv[i++] = ft_strdup(arg);
	tail->argv = argv;
	tail->argc = i;
	return (0);
}
