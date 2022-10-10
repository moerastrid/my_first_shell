/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buildin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 19:20:52 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 20:27:02 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_del(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_buildin(t_simple	t)
{
	if (ft_strncmp(t.argv[0], "echo", 4) == 0 && is_del(t.argv[0][5]) == 1)
		return (1);
	if (ft_strncmp(t.argv[0], "cd", 2) == 0 && is_del(t.argv[0][3]) == 1)
		return (1);
	if (ft_strncmp(t.argv[0], "pwd", 3) == 0 && is_del(t.argv[0][4]) == 1)
		return (1);
	if (ft_strncmp(t.argv[0], "export", 6) == 0 && is_del(t.argv[0][7]) == 1)
		return (1);
	if (ft_strncmp(t.argv[0], "unset", 5) == 0 && is_del(t.argv[0][6]) == 1)
		return (1);
	if (ft_strncmp(t.argv[0], "env", 3) == 0 && is_del(t.argv[0][4]) == 1)
		return (1);
	if (ft_strncmp(t.argv[0], "exit", 4) == 0 && is_del(t.argv[0][5]) == 1)
		return (1);
	return (0);
}

void	exec_buildin(t_simple t)
{
printf("argc: %d\nargv: %s\nbin: %s\n\n", t.argc, t.argv[0], t.bin);

	ft_putstr_fd("exit!!!!!\n", 2);

	exit(5);
}