/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 21:27:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
// IN single.c, THE SINGLE COMMANDS ARE EXECUTED

// Execute a single command in a child process
void	exec_cmd(t_simple *simple, char **envp)
{
	int	i;

	i = 1;
	default_signals();
	if (simple->bin)
		execve(simple->bin, simple->argv, envp);
	if (simple->bin && access(simple->bin, F_OK) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(simple->argv[0], STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		exit (126);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(simple->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit (127);
	}
}

static int	signal_catcher(pid_t child_pid)
{
	int		status;
	int		exit_code;

	exit_code = 0;
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	return (exit_code);
}

// this is a function for a single command
// executed in a single child process
int	only_child(t_cmd *cmd)
{
	pid_t	child_id;
	int		ret1;
	int		ret2;

	child_id = fork();
	if (child_id == -1)
		return (10);
	else if (child_id == 0)
	{
		ret1 = redirect_infile(cmd->simples->infiles);
		ret2 = redirect_outfile(cmd->simples->outfiles);
		if (!ret1 && !ret2)
			exec_cmd(cmd->simples, cmd->envc);
		else
			exit (ret1 || ret2);
	}
	else
		return (signal_catcher(child_id));
	return (1);
}
