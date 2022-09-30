/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute01.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/30 00:34:59 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

int	family_life(t_cmd cmds)
{
	int		pfd[2][2];
	int		i;
	int		*children;

	children = ft_calloc(cmds.cmd_count, sizeof(int));
	if (children == NULL)
		return (-1);
	i = 0;
	while (i < cmds.cmd_count)
	{
		if (i + 1 != cmds.cmd_count)
			pipe(pfd[i % 2]);
		children[i] = child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (children[i] == -1)
			return (-1);
		i++;
	}
	return (parent(children, cmds, pfd[(i + 1) % 2]));
}

int	parent(int *children, t_cmd cmds, int *pfd)
{
	int	status;
	int	exit_code;
	int	i;

	exit_code = 0;
	status = 0;
	i = 0;
	while (i < cmds.cmd_count)
	{
		waitpid(children[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	free(children);
	dprintf(STDERR_FILENO, "exit_code : %d \n", exit_code);
	return (exit_code);
}

void	child_2(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	if (cmd_no != 0)
	{
		if (dup2(read_pipe[READ], STDIN_FILENO) == -1)
			exit (-1);
	}
	if (cmd_no != cmds.cmd_count - 1)
	{
		if (dup2(write_pipe[WRITE], STDOUT_FILENO) == -1)
			exit (-1);
	}
}

int	child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == -1)
		return (-1);
	else if (child_id != 0)
	{
		if (cmd_no != 0)
			close(read_pipe[READ]);
		if (cmd_no != cmds.cmd_count)
			close (write_pipe[WRITE]);
		return (child_id);
	}
	close(write_pipe[READ]);
	child_2(cmds, write_pipe, read_pipe, cmd_no);
	exec_cmd(cmds.simples[cmd_no]);
	dprintf(STDERR_FILENO, "cmd %d not found\n", cmd_no);
	close(write_pipe[WRITE]);
	exit (-1);
}
