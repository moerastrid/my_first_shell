/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute00.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:17:33 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// EXECUTE00 IS THE EXECUTE MAIN STRUCTURE 

int	execute(t_cmd cmds)
{
	pid_t	stdin;
	pid_t	stdout;
	pid_t	stderr;

	if (cmds.amount_cmd <= 0)
		return (-1);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	stderr = dup(STDERR_FILENO);
	if (stdout == -1 || stdout == -1 || stderr == -1)
		return (-1);
	if (cmds.amount_cmd == 1)
	{
		if (exec_single_cmd(cmds) != 0)
			return (-1);
	}
	else
	{
		if (family_life(cmds) != 0)
			return (-1);
	}
	return (0);
}