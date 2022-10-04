/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute01.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 22:58:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

t_children	*newchild(pid_t id)
{
	t_children	*new;

	new = ft_calloc(1, sizeof(t_children));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->next = NULL;
	return (new);
}

void	childaddback(t_children *current, t_children *new)
{
	t_children	*temp;

	*temp = *current;
	if (current == NULL)
		current = new;
	while (temp != NULL)
		temp = temp->next;
	temp = new;
}

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
			pipe(pfd[i % 2]);
		id = child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (id == -1)
			exit(-1); //?
		new = newchild(id);
		childaddback(&g_children, new);
		i++;
	}
	return (parent(cmds, pfd[(i + 1) % 2]));
}

int	parent(t_cmd cmds, int *pfd)
{
	int			status;
	int			exit_code;
	t_children	*temp;

	*temp = g_children;
	exit_code = 0;
	status = 0;
	while (temp)
	{
		waitpid(temp->id, &status, 0);
		temp = temp->next;
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
	}
	if (cmd_no != cmds.cmd_count - 1)
	{
		if (dup2(write_pipe[WRITE], STDOUT_FILENO) == -1)
			exit (-1);
	}
}

t_simple	*get_simple(t_cmd cmd, int num)
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
	else if (child_id != 0)
	{
		if (cmd_no != 0)
			close(read_pipe[READ]);
		if (cmd_no != cmds.cmd_count)
			close (write_pipe[WRITE]);
		return (child_id);
	}
	close(write_pipe[READ]);
	child_redirect(cmds, write_pipe, read_pipe, cmd_no);
	simple = get_simple(cmds, cmd_no);
	exec_cmd(*simple);
	return (-1);
}
