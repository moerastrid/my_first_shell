/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute00.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 21:50:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE00 IS THE EXECUTE MAIN

int	execute(t_cmd cmds, t_token *tokens)
{
	if (cmds.cmd_count <= 0)
		return (-1);
	if (cmds.cmd_count == 1)
	{
		if (is_buildin(cmds.simples) == 1)
			exec_buildin(cmds, tokens);
		else if (only_child(cmds) != 0)
			return (-1);
	}
	else
	{
		if (family_life(cmds) != 0)
			return (-1);
	}
	return (0);
}
