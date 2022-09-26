/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 14:57:15 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/// @brief	here we execute one command
/// @param	cmds the list with all commands
/// @param	cmd_no	the command we want to execute
void	exec_cmd(t_cmd cmds, int cmd_no)
{
	dprintf(2, "cmd %d is executed\n", cmd_no);
	exit(0);
}
