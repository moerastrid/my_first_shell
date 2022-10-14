/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:07 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 18:43:56 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_outfile(t_cmd *cmd, int append_mode, char *data)
{
	if (cmd->outfiles == NULL)
		cmd->outfiles = str_list_new(data, append_mode);
	else
		str_list_add_back(cmd->outfiles, str_list_new(data, append_mode));
}

void	add_infile(t_cmd *cmd, char *data)
{
	if (cmd->infiles == NULL)
		cmd->infiles = str_list_new(data, -1);
	else
		str_list_add_back(cmd->infiles, str_list_new(data, -1));
}

void	add_delimiter(t_cmd *cmd, char *data)
{
	if (cmd->delimiters == NULL)
		cmd->delimiters = str_list_new(data, -1);
	else
		str_list_add_back(cmd->delimiters, str_list_new(data, -1));
}

int	add_arg(t_simple *simple, char *arg)
{
	char	**argv;
	int		i;

	i = 0;
	argv = ft_calloc(sizeof(char *), (simple->argc + 2));
	if (argv == NULL)
		return (-1);
	while (i < simple->argc)
	{
		argv[i] = simple->argv[i];
		i++;
	}
	if (simple->argv)
		free(simple->argv);
	argv[i++] = ft_strdup(arg);
	simple->argv = argv;
	simple->argc = i;
	return (0);
}
