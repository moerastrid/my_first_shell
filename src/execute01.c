/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute01.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:15:34 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

int	family_life(t_cmd cmds)
{
	int		pfd[2][2];
	int		i;
	int		*children;

	children = ft_calloc(cmds.amount_cmd, sizeof(int));
	if (children == NULL)
		return (-1);
	i = 0;
	while (i < cmds.amount_cmd)
	{
		if (i + 1 != cmds.amount_cmd)
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
	while (i < cmds.amount_cmd)
	{
		waitpid(children[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	free(children);
	dprintf(1, "exit_code : %d \n", exit_code);
	return (exit_code);
}

void	child_2(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	if (cmd_no != 0)
	{
		if (dup2(read_pipe[READ], STDIN_FILENO) == -1)
			exit (-1);
	}
	if (cmd_no != cmds.amount_cmd - 1)
	{
		if (dup2(write_pipe[WRITE], STDOUT_FILENO) == -1)
			exit (-1);
	}
}

int	child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	pid_t	child_one_id;

	child_one_id = fork();
	if (child_one_id == -1)
		return (-1);
	else if (child_one_id == 0)
	{
		close(write_pipe[READ]);
		child_2(cmds, write_pipe, read_pipe, cmd_no);
		exec_cmd(cmds, cmd_no);
		close(write_pipe[WRITE]);
		return (-1);
	}
	else
	{
		if (cmd_no != 0)
			close(read_pipe[READ]);
		if (cmd_no != cmds.amount_cmd)
			close (write_pipe[WRITE]);
		return (child_one_id);
	}
}
