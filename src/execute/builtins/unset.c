/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:02:35 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 20:47:55 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_unset(t_simple simple, t_cmd *cmd)
{
	int		i;
	char	**new_envc;

	i = 1;
	while (simple.argv[i])
	{
		new_envc = env_remove(simple.argv[i], cmd->envc);
		cmd->envc = new_envc;
		i++;
	}
	return (0);
}
