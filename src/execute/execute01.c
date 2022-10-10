/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute01.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 23:51:59 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

int	family_life(t_cmd cmds)
{
	int			pfd[2][2];
	int			i;
	t_children	*new;
	pid_t		id;

	i = 0;
	while (i < cmds.cmd_count)
	{
		if (i != cmds.cmd_count - 1)
		{
			if (pipe(pfd[i % 2]) == -1)
				perror("pipe error");
		}
		id = child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (id == -1)
			return (-1);
		new = new_child(id);
		if (g_children == NULL)
			g_children = new;
		else
			child_add_back(g_children, new);
		i++;
	}
	return (pickup_kids());
}

int	pickup_kids(void)
{
	int			status;
	int			exit_code;
	t_children	*child;

	child = g_children;
	exit_code = 0;
	status = 0;
	while (child)
	{
		waitpid(child->id, &status, 0);
		child = child->next;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	return (exit_code);
}

static void	child_redirect(t_cmd cmd, int *writep, int *readp, int cmd_no)
{
	if (cmd_no != 0)
	{
		if (dup2(readp[READ], STDIN_FILENO) == -1)
			exit (-1);
		close (readp[READ]);
	}
	if (cmd_no != cmd.cmd_count - 1)
	{
		if (dup2(writep[WRITE], STDOUT_FILENO) == -1)
			exit (-1);
		close (writep[WRITE]);
	}
	if (cmd_no == 0)
		redirect_infile(cmd.infiles);
	if (cmd_no == cmd.cmd_count - 1)
		redirect_outfile(cmd.outfiles);
}

static t_simple	*get_simple(t_cmd cmd, int num)
{
	int			i;
	t_simple	*simple;

	simple = cmd.simples;
	i = 0;
	while (i < num)
	{
		simple = simple->next;
		i++;
	}
	return (simple);
}

pid_t	child(t_cmd cmd, int *writep, int *readp, int cmd_no)
{
	pid_t		child_id;
	t_simple	*simple;

	child_id = fork();
	if (child_id < 0)
		return (-1);
	else if (child_id == 0)
	{
		close(writep[READ]);
		child_redirect(cmd, writep, readp, cmd_no);
		simple = get_simple(cmd, cmd_no);
		if (is_buildin(simple) == 1)
		{
			exec_buildin(simple, cmd, NULL);
			exit (0);
		}
		else
			exec_cmd(simple, cmd.envp);
		return (-1);
	}
	else // parent
	{
		if (cmd_no != 0)
			close(readp[READ]);
		if (cmd_no != cmd.cmd_count - 1)
			close (writep[WRITE]);
		return (child_id);
	}
}

//											Parent
// Pipes		[[write, read],[write, read]]			[[write, read],[write, read]]
// cmd1							| 				cmd2				| cmd3
// c1 							| 				c2 					| c3
// Reads from stdin				| 				reads from pipe		| reads from pipe
// Writes to pipe				| 				Writes to pipe		| Writes to stdout
