/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 22:43:35 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_export(t_simple simple, t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!simple.argv[1])
	{
		while (cmd->envc[i] != NULL)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			//while (cmd->envc[i][j] != '\0')
			//{
			//	ft_putchar_fd(cmd->envc[i][j], STDOUT_FILENO);
			//	if (cmd->envc[i][j] == '=')
			//		ft_putstr_fd("\"", STDOUT_FILENO);
			//	j++;
			//}
			//ft_putstr_fd("\"\n", STDOUT_FILENO);
			i++;
		}
	}
	i = 1;
	while (simple.argv[i])
	{
		cmd->envc = env_add(simple.argv[i], cmd->envc);
		i++;
	}
	return (0);
}
