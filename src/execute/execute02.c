/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute02.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 22:51:34 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE02, THE SINGLE COMMANDS ARE EXECUTED

// this is a single command in a child process
void	exec_cmd(t_simple simple)
{
	int i;

	execve(simple.bin, simple.argv, NULL);
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	i = 0;
	while (simple.argv[i])
	{
		ft_putstr_fd(simple.argv[i], STDERR_FILENO);
		i++;
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	exit (0);
}

void redirect_infile(t_str_list *infiles)
{
	int	fd;

	if (!infiles)
		return ;
	while (infiles->next)
		infiles = infiles->next;
	fd = open(infiles->str, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void redirect_outfile(t_str_list *outfiles)
{
	int	fd;
	int	flags;

	if (outfiles == NULL)
		return ;
	while (outfiles != NULL)
	{
		fd = open(outfiles->str, O_CREAT, 0666);
		close(fd);
		if (outfiles->next == NULL)
			break;
		outfiles = outfiles->next;
	}
	if (outfiles->append_mode)
		flags = O_RDWR | O_APPEND;
	else
		flags = O_WRONLY;
	fd = open(outfiles->str, flags, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

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
	{
		redirect_infile(cmds.infiles);
		redirect_outfile(cmds.outfiles);
		exec_cmd(cmds.simples[0]);
	}
	else
	{
		g_children = new_child(child_one_id);
		waitpid(child_one_id, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status) + 128;
		return (exit_code);
	}
	return (0);
}
