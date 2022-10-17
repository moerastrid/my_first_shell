/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 14:28:30 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_export(t_simple simple, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (simple.argv[i])
	{
		cmd->envc = env_add(simple.argv[i], cmd->envc);
		i++;
	}
	return (0);
}
