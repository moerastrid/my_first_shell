/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   family_life.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 13:21:33 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

static int	pickup_kids(t_children *kids)
{
	int			status;
	int			exit_code;

	exit_code = 0;
	status = 0;
	while (kids)
	{
		waitpid(kids->id, &status, 0);
		kids = kids->next;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	return (exit_code);
}

int	family_life(t_cmd cmds)
{
	int			pfd[2][2];
	int			i;
	t_children	*new;
	t_children	*kids;
	pid_t		id;

	i = 0;
	kids = NULL;
	while (i < cmds.cmd_count)
	{
		if (i != cmds.cmd_count - 1)
		{
			if (pipe(pfd[i % 2]) == -1)
				perror("pipe error");
		}
		id = create_child(cmds, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (id == -1)
			return (-1);
		new = new_child(id);
		if (kids == NULL)
			kids = new;
		else
			child_add_back(kids, new);
		i++;
	}
	return (pickup_kids(kids));
}

void	parent(t_cmd cmd, int *writep, int *readp, int cmd_no)
{
	if (cmd_no != 0)
		close(readp[READ]);
	if (cmd_no != cmd.cmd_count - 1)
		close (writep[WRITE]);
}

pid_t	create_child(t_cmd cmd, int *writep, int *readp, int cmd_no)
{
	pid_t		child_id;

	child_id = fork();
	if (child_id < 0)
		return (-1);
	else if (child_id == 0)
	{
		child(cmd, writep, readp, cmd_no);
		return (-1);
	}
	else
	{
		parent(cmd, writep, readp, cmd_no);
		return (child_id);
	}
}
