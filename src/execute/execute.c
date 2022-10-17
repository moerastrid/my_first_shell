/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 23:21:38 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE00 IS THE EXECUTE MAIN

int	execute(t_cmd *cmd)
{
	int	ret_val;

	ret_val = 0;
	ignore_signals();
	if (cmd->cmd_count <= 0)
		return (-1);
	if (cmd->cmd_count == 1)
	{
		if (ft_strncmp(cmd->simples->argv[0], "exit", 5) == 0)
			exit (0);
		return (only_child(cmd));
	}
	else
		return (family_life(cmd));
}
