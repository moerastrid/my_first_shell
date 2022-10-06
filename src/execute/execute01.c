/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:18:38 by ageels            #+#    #+#             */
/*   Updated: 2022/10/06 17:41:40 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

int	family_life(t_cmd cmds)
{
	int			pfd[2][2];
	int			res;
	int			i;
	t_children	*new;
	pid_t		id;

	i = 0;

	while (i < cmds.cmd_count)
	{
		if (i != cmds.cmd_count - 1) // Pipe for all but the last iteration
		{
			res = pipe(pfd[i % 2]);
			if(res == -1)
				perror("pipe error");
		}
		printf("Pipe0: [%d, ", pfd[0][0]);
		printf("%d] => ", pfd[0][1]);
		printf("Pipe1: [%d, ", pfd[1][0]);
		printf("%d]\n", pfd[1][1]);
		id = child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (id == -1)
			return(-1);
		new = new_child(id);
		if (g_children == NULL)
			g_children = new;
		else
			child_add_back(g_children, new);
		i++;
	}
	return (pickup());//cmds, pfd[(i + 1) % 2]));
}

int	pickup()//t_cmd cmds, int *pfd)
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

void	child_redirect(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	if (cmd_no != 0)
	{
		if (dup2(read_pipe[READ], STDIN_FILENO) == -1)
			exit (-1);
		close(read_pipe[READ]);
	}
	if (cmd_no != cmds.cmd_count - 1)
	{
		if (dup2(write_pipe[WRITE], STDOUT_FILENO) == -1)
			exit (-1);
		close(write_pipe[WRITE]);
	}
	if (cmd_no == 0)
		redirect_infile(cmds.infiles);
	if (cmd_no == cmds.cmd_count - 1)
		redirect_outfile(cmds.outfiles);
	// system("lsof -c minishell");
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

pid_t	child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no)
{
	pid_t		child_id;
	t_simple	*simple;

	child_id = fork();
	if (child_id == -1)
		return (-1);
	else if (child_id != 0) //parent
	{
		if (cmd_no != 0)
			close(read_pipe[READ]);
		if (cmd_no != cmds.cmd_count - 1)
			close(write_pipe[WRITE]);
		return (child_id);
	}
	close(write_pipe[READ]);
	child_redirect(cmds, write_pipe, read_pipe, cmd_no);
	simple = get_simple(cmds, cmd_no);
	exec_cmd(*simple);
	return (-1);
}
//											Parent
// Pipes		[[write, read],[write, read]]			[[write, read],[write, read]]
// cmd1							| 				cmd2				| cmd3
// c1 							| 				c2 					| c3
// Reads from stdin				| 				reads from pipe		| reads from pipe
// Writes to pipe				| 				Writes to pipe		| Writes to stdout
