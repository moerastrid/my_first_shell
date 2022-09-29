/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute02.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/29 21:11:32 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

// IN EXECUTE02, THE SINGLE COMMANDS ARE EXECUTED

// this is a single command in a child process 
void	exec_cmd(t_cmd cmds, int cmd_no)
{
	dprintf(STDOUT_FILENO, "cmd %d is executed\n", cmd_no);
	
	//execve
}

// this is a single command in a single process (when there is only 1 command) 
// hier dus zorgen dat hij naar exec_cmd gaat !
int single_parent(t_cmd cmds)
{
	//fork()
	//exec_cmd()
	//waitpid()
	//etc..
	dprintf(STDERR_FILENO, "single cmd is executed\n");
	return (0);
}
