/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:19:29 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_isflag(char *str)
{
	if (*str == '-')
		str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

int	bi_echo(t_simple *sm)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (sm->argc <= 1)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	while (sm->argv[i] && ft_isflag(sm->argv[i]))
	{
		flag = 1;
		i++;
	}
	while (sm->argv[i] != NULL)
	{
		ft_putstr_fd(sm->argv[i], STDOUT_FILENO);
		if (sm->argv[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		if (sm->argv[i + 1] == NULL && flag == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
