/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:19:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/03 16:54:26 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
// IN single.c, THE SINGLE COMMANDS ARE EXECUTED

// Execute a single command in a child process
void	exec_cmd(t_simple *simple, char **envp)
{
	default_signals();
	if (simple->bin)
		execve(simple->bin, simple->argv, envp);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (simple->bin && access(simple->bin, F_OK) == 0)
	{
		printf("minishell: ");
		if (access(simple->bin, X_OK) != 0)
			printf("%s : Permission denied\n", simple->argv[0]);
		else
			printf("%s : is a directory\n", simple->argv[0]);
		exit (126);
	}
	else if (simple->argv)
	{
		printf("minishell: %s", simple->argv[0]);
		if (ft_strchr(simple->argv[0], '/') != NULL)
			printf(": No such file or directory\n");
		else
			printf(": command not found\n");
		exit (127);
	}
	exit(0);
}

void	catch_errno(int err)
{
	if (err == 130)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	else if (err == 131)
		ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
}

int	signal_catcher(pid_t child_pid)
{
	int		status;
	int		exit_code;

	exit_code = 0;
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	catch_errno(exit_code);
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
