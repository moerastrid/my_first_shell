/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_bin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:44 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:29:50 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_bin(t_simple *simple, char **paths)
{
	char	*myexec;
	int		i;

	if (!simple || !simple->argv)
		return ;
	if (ft_strchr(simple->argv[0], '/') != NULL)
	{
		simple->bin = ft_strdup(simple->argv[0]);
		return ;
	}
	i = 0;
	while (paths && paths[i])
	{
		myexec = ft_strjoin3(paths[i++], "/", simple->argv[0]);
		if (!myexec)
			return ;
		if (access(myexec, X_OK) == 0)
		{
			simple->bin = myexec;
			return ;
		}
		free (myexec);
	}
	return ;
}

void	cmd_simples_set_bin(t_cmd *cmd)
{
	t_simple	*simples;
	char		*argv0;

	simples = cmd->simples;
	while (simples)
	{
		if (simples->argv)
		{
			argv0 = simples->argv[0];
			if (argv0 && ft_strlen(argv0) != 0)
				set_bin(simples, cmd->paths);
		}
		simples = simples->next;
	}
}
