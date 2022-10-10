/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins00.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 22:27:41 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	bi_echo(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	//exit (0);
}

void	bi_cd(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	//exit (0);
}

void	bi_pwd(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	//exit (0);
}

void	bi_export(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	//exit (0);
}

void	bi_unset(void)
{
	ft_putstr_fd("buildin is executed\n", 1);
	//exit (0);
}

void	bi_env(t_cmd cmd)
{
	int	i;

	ft_putstr_fd("buildin env is executed\n", STDOUT_FILENO);
	i = 0;
	//while (cmd.envp[i] != NULL)
	//{
	//	ft_putstr_fd(cmd.envp[i], STDOUT_FILENO);
	//	ft_putstr_fd("\n", STDOUT_FILENO);
	//	i++;
	//}
	//exit (0);
}

void	bi_exit(t_cmd cmd, t_token *tokens)
{
	kill_children(g_children);
	free_children(g_children);
	g_children = NULL;
	clear_cmd(&cmd);
	if (tokens)
		free_token_list(tokens);
	ft_putstr_fd("exit\n", 1);
	exit (0);
}
