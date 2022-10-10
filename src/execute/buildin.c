/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buildin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 20:45:09 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 22:23:29 by ageels        ########   odam.nl         */
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

int	is_buildin(t_simple	*t)
{
	if (!t)
		return (0);
	// printf("argc: %d\nargv: %s\nbin: %s\n\n", t->argc, t->argv[0], t->bin);
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

void	exec_buildin(t_cmd cmd, t_token *tokens)
{
	if (ft_strncmp(cmd.simples->argv[0], "echo", 5) == 0)
		bi_echo();
	if (ft_strncmp(cmd.simples->argv[0], "cd", 3) == 0)
		bi_cd();
	if (ft_strncmp(cmd.simples->argv[0], "pwd", 4) == 0)
		bi_pwd();
	if (ft_strncmp(cmd.simples->argv[0], "export", 7) == 0)
		bi_export();
	if (ft_strncmp(cmd.simples->argv[0], "unset", 6) == 0)
		bi_unset();
	if (ft_strncmp(cmd.simples->argv[0], "env", 4) == 0)
		bi_env(cmd);
	if (ft_strncmp(cmd.simples->argv[0], "exit", 5) == 0)
		bi_exit(cmd, tokens);
}
