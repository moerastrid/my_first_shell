/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buildin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 20:45:09 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 21:40:05 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_del(char c)
{
	if (c == ' ' || c == '\0' || c == '\n')
		return (1);
	return (0);
}

int	is_buildin(t_simple	*t)
{
	if (!t)
		return (0);
	printf("argc: %d\nargv: %s\nbin: %s\n\n", t->argc, t->argv[0], t->bin);
	if (ft_strncmp(t->argv[0], "echo", 4) == 0 && is_del(t->argv[0][5]) == 1)
		return (1);
	if (ft_strncmp(t->argv[0], "cd", 2) == 0 && is_del(t->argv[0][3]) == 1)
		return (1);
	if (ft_strncmp(t->argv[0], "pwd", 3) == 0 && is_del(t->argv[0][4]) == 1)
		return (1);
	if (ft_strncmp(t->argv[0], "export", 6) == 0 && is_del(t->argv[0][7]) == 1)
		return (1);
	if (ft_strncmp(t->argv[0], "unset", 5) == 0 && is_del(t->argv[0][6]) == 1)
		return (1);
	if (ft_strncmp(t->argv[0], "env", 3) == 0 && is_del(t->argv[0][4]) == 1)
		return (1);
	if (ft_strncmp(t->argv[0], "exit", 4) == 0 && is_del(t->argv[0][5]) == 1)
		return (1);
	return (0);
}

void	exec_buildin(t_cmd cmd, t_token *tokens)
{
	if (ft_strncmp(cmd.simples->argv[0], "echo", 4) == 0 && is_del(cmd.simples->argv[0][5]) == 1)
		bi_echo();
	if (ft_strncmp(cmd.simples->argv[0], "cd", 2) == 0 && is_del(cmd.simples->argv[0][3]) == 1)
		bi_cd();
	if (ft_strncmp(cmd.simples->argv[0], "pwd", 3) == 0 && is_del(cmd.simples->argv[0][4]) == 1)
		bi_pwd();
	if (ft_strncmp(cmd.simples->argv[0], "export", 6) == 0 && is_del(cmd.simples->argv[0][7]) == 1)
		bi_export();
	if (ft_strncmp(cmd.simples->argv[0], "unset", 5) == 0 && is_del(cmd.simples->argv[0][6]) == 1)
		bi_unset();
	if (ft_strncmp(cmd.simples->argv[0], "env", 3) == 0 && is_del(cmd.simples->argv[0][4]) == 1)
		bi_env();
	if (ft_strncmp(cmd.simples->argv[0], "exit", 4) == 0 && is_del(cmd.simples->argv[0][5]) == 1)
		bi_exit(cmd, tokens);
}
