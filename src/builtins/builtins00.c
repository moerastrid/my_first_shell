/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins00.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/12 19:21:48 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bi_echo(t_simple *simple)
{
	int	flag;
	int i;

	flag = 0;
	i = 1;
	if (simple->argc == 1)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strlen(simple->argv[1]) > 1 && ft_strncmp("-n", simple->argv[1], 3) == 0)
	{
		flag = 1;
		i++;
	}
	while(simple->argv[i] != NULL)
	{
		ft_putstr_fd(simple->argv[i], STDOUT_FILENO);
		if (simple->argv[i+1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (simple->argv[i+1] == NULL && flag == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	bi_cd(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	return (0);
}

int	bi_pwd(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	return (0);
}

int	bi_export(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	return (0);
}

int	bi_unset(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	return (0);
}

int	bi_env(t_cmd cmd)
{
	int	i;

	ft_putstr_fd("buildin env is executed\n", STDOUT_FILENO);
	i = 0;
	while (cmd.envp[i] != NULL)
	{
		ft_putstr_fd(cmd.envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}

void	bi_exit(t_cmd cmd, t_token *tokens)
{
	kill_children(g_children);
	free_children(g_children);
	g_children = NULL;
	clear_cmd(&cmd);
	if (tokens)
		free_token_list(tokens);
	dprintf(2, "command count : %d\n", cmd.cmd_count);
	if (cmd.cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit (0);
}
