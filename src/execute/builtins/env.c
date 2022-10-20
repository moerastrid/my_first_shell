/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 20:47:14 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->envc[i] != NULL)
	{
		ft_putstr_fd(cmd->envc[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
