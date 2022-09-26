/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thefam.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 14:13:07 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief	setup of the child processes and the parent
///			who catches their return value at the end
/// @param	total_cmd the total amounds of commands between pipes.
/// @param	cmds this needs to be a list of commands 
///			we can pass to the execute function
/// @return	exit code of the parent process
int	family_life(int total_cmd, t_list *cmds)
{
	pid_t	stdin;
	pid_t	stdout;
	pid_t	stderr;
	int		pfd[2][2];
	int		i;
	int		*children;

	children = ft_calloc(total_cmd, sizeof(int));
	if (children == NULL)
		return (-1);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	strerr = dup(STDERR_FILENO);
	if (stdout == -1 || stdout == -1)
		exit (-1);
	i = 0;
	while (i < total_cmd)
	{
		if (i + 1 != total_cmd)
			pipe(pfd[i % 2]);
		children[i] = child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i, total_cmd);
		if (children[i] == -1)
			return (-1);
		i++;
	}
	return (parent(children, total_cmd, pfd[(i + 1) % 2]));
}

/// @brief		The parent process waits for the child processes 
///				to have finished
///				and checks their return status (see if they succeeded in life)
/// @param 		children : PID's of the child processes
/// @param 		total_cmd
/// @param 		pfd : pipe fd of the last open pipe
/// @return 	the exit code of the waitpid status return
///				(exit code of child processes)
int	parent(int *children, int total_cmd, int *pfd)
{
	int	status;
	int	exit_code;
	int	i;

	exit_code = 0;
	status = 0;
	i = 0;
	while (i < total_cmd)
	{
		waitpid(children[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	free(children);
	return (exit_code);
}

/// @brief				The child processes execute 1 cmd each
/// @param write_pipe	the pipe to write to
/// @param read_pipe	the pipe to read from
/// @param cmd_no		current command
/// @param total_cmd	total amounth of commands
/// @return				the child ID of the fork (or an exit_code)
int	child(t_list *cmds, int *write_pipe, int *read_pipe, int cmd_no, int total_cmd)
{
	pid_t	child_one_id;

	child_one_id = fork();
	if (child_one_id == -1)
		return (-1);
	else if (child_one_id == 0)
	{
		close(write_pipe[READ]);
		if (cmd_no != 0)
		{
			if (dup2(read_pipe[READ], STDIN_FILENO) == -1)
				exit (-1);
		}
		if (cmd_no != total_cmd)
		{	
			if (dup2(write_pipe[WRITE], STDOUT_FILENO) == -1)
				exit (-1);
		}
		exec_cmd(cmds, cmd_no);
		ft_putstr_fd("this aint no command", 1);
		close(write_pipe[WRITE]);
		return (-1);
	}
	else
	{
		if (cmd_no != 0)
			close(read_pipe[READ]);
		if (cmd_no != total_cmd)
			close (write_pipe[WRITE]);
		return (child_one_id);
	}
}
