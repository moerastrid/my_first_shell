/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute02.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 19:16:38 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE02, THE SINGLE COMMANDS ARE EXECUTED

// this is a single command in a child process 
void	exec_cmd(t_simple simple)
{
	execve(simple.bin, simple.argv, NULL);
}

// PUT INSIDE EXEC_CMD FOR DEBUGGING:
	//int i;

	//i = 0;
	//printf("simple bin: %s\n", simple.bin);
	//while (simple.argv[i])
	//{
	//	printf("simple arg %d : %s\n", i, simple.argv[i]);
	//	i++;
	//}
	//printf("command is succesfull executed! \n");
	//exit (0);

// this is a function for a single command
// executed in a single child process
int	only_child(t_cmd cmds)
{
	pid_t	child_one_id;
	int		status;
	int		exit_code;

	child_one_id = fork();
	if (child_one_id == -1)
		return (-1);
	else if (child_one_id == 0)
		exec_cmd(cmds.simples[0]);
	else
	{
		waitpid(child_one_id, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status) + 128;
		return (exit_code);
	}
	dprintf(STDERR_FILENO, "single cmd is executed\n");
	return (0);
}
