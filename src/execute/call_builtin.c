/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   call_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 20:45:09 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:37:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(t_simple *simple)
{
	char	*s;

	if (simple->argv == NULL)
		return (0);
	s = simple->argv[0];
	if (ft_strncmp(s, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(s, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(s, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(s, "export", 7) == 0)
		return (1);
	if (ft_strncmp(s, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(s, "env", 4) == 0)
		return (1);
	if (ft_strncmp(s, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_simple	*t, t_cmd *cmd)
{
	if (ft_strncmp(t->argv[0], "echo", 5) == 0)
		return (bi_echo(t));
	else if (ft_strncmp(t->argv[0], "cd", 3) == 0)
		return (bi_cd(t, cmd));
	else if (ft_strncmp(t->argv[0], "pwd", 4) == 0)
		return (bi_pwd());
	else if (ft_strncmp(t->argv[0], "export", 7) == 0)
		return (bi_export(*t, cmd));
	else if (ft_strncmp(t->argv[0], "unset", 6) == 0)
		return (bi_unset(*t, cmd));
	else if (ft_strncmp(t->argv[0], "env", 4) == 0)
		return (bi_env(cmd));
	else if (ft_strncmp(t->argv[0], "exit", 5) == 0)
	{
		bi_exit(cmd, t);
		ft_putstr_fd("exit error\n", STDERR_FILENO);
		clear_cmd(cmd);
		exit(1);
	}
	else
	{
		ft_putstr_fd("builtin error\n", STDERR_FILENO);
		return (1);
	}
}
