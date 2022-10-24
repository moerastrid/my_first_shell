/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 23:23:16 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_export(t_simple simple, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!simple.argv[1])
	{
		while (cmd->envc[i] != NULL)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(cmd->envc[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			i++;
		}
	}
	i = 1;
	while (simple.argv[i])
	{
		cmd->envc = env_add(simple.argv[i], cmd->envc);
		i++;
	}
	printf("%s\n", cmd->envc[0]);
	return (0);
}
