/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 23:24:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE03, THE SINGLE COMMANDS ARE EXECUTED

// this is a single command in a child process
void	exec_cmd(t_simple *simple, char **envp)
{
	int	i;

	default_signals();
	execve(simple->bin, simple->argv, envp);
	i = 0;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	while (simple->argv[i])
	{
		ft_putstr_fd(simple->argv[i], STDERR_FILENO);
		i++;
	}
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	g_errno = 2;
	exit (1);
}

// this is a function for a single command
// executed in a single child process
int	only_child(t_cmd *cmd)
{
	pid_t	child_one_id;
	int		status;
	int		exit_code;
	int		ret_val;

	exit_code = 0;
	child_one_id = fork();
	if (child_one_id == -1)
		return (-1);
	else if (child_one_id == 0)
	{
		redirect_infile(cmd->infiles);
		redirect_outfile(cmd->outfiles);
		if (is_builtin(cmd->simples) == 1)
		{
			if (errno == 2)
				errno = 0;
			ret_val = exec_builtin(cmd->simples, cmd);
			dup2(0, STDIN_FILENO);
			dup2(1, STDOUT_FILENO);
			exit (ret_val);
		}
		else
			exec_cmd(cmd->simples, cmd->envc);
	}
	else
	{
		waitpid(child_one_id, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status) + 128;
		return (exit_code);
	}
	return (0);
}
