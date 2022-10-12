/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 20:45:09 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/12 19:34:18 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_del(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\0' || c == '\n')
		return (1);
	return (0);
}

int	is_builtin(t_simple	*t)
{
	//if (t == NULL)
	//	return (0);
	//dprintf(2, "ASTRIDDEBUG\nargc: %d\nargv: %s\nbin: %s\n\n", t->argc, t->argv[0], t->bin);
	if (ft_strncmp(t->argv[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(t->argv[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(t->argv[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(t->argv[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(t->argv[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(t->argv[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(t->argv[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_simple	*t, t_cmd cmd, t_token *tokens)
{
	if (ft_strncmp(t->argv[0], "echo", 5) == 0)
		return (bi_echo(t));
	else if (ft_strncmp(t->argv[0], "cd", 3) == 0)
		return (bi_cd());
	else if (ft_strncmp(t->argv[0], "pwd", 4) == 0)
		return (bi_pwd(cmd));
	else if (ft_strncmp(t->argv[0], "export", 7) == 0)
		return (bi_export());
	else if (ft_strncmp(t->argv[0], "unset", 6) == 0)
		return (bi_unset());
	else if (ft_strncmp(t->argv[0], "env", 4) == 0)
		return (bi_env(cmd));
	else if (ft_strncmp(t->argv[0], "exit", 5) == 0)
	{
		bi_exit(cmd, tokens);
		ft_putstr_fd("exit error\n", STDERR_FILENO);
		exit(1);
	}
	else
	{
		ft_putstr_fd("builtin error\n", STDERR_FILENO);
		return (1);
	}
}
