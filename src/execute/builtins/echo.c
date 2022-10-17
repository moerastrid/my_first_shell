/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 22:46:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_echo(t_simple *sm)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (sm->argc == 1)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strlen(sm->argv[1]) > 1 && ft_strncmp("-n", sm->argv[1], 3) == 0)
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
