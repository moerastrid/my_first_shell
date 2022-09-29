/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute02.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/29 21:53:25 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

// IN EXECUTE02, THE SINGLE COMMANDS ARE EXECUTED

// this is a single command in a child process 
void	exec_cmd(t_cmd cmds, int cmd_no)
{
	char	*my_exec;
	char	**my_array;
	int		i;

	my_array = single_split(cmds.simples->argv[cmd_no], ' ');
	if (my_array == NULL)
		exit(-1);
	//my_exec = getexec(my_array[0], cmds.paths);
	dprintf(STDERR_FILENO, "cmd %d is executed\n", cmd_no);

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
