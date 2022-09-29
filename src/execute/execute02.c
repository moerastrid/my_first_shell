/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute02.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/29 17:42:07 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

// IN EXECUTE02, THE SINGLE COMMANDS ARE EXECUTED

void	exec_cmd(t_cmd cmds, int cmd_no)
{
	dprintf(2, "cmd %d is executed\n", cmd_no);
	exit(0);
}

int	exec_single_cmd(t_cmd cmds)
{
	dprintf(2, "single cmd is executed\n");
	return (0);
}
