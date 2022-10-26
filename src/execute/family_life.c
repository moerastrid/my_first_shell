/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   family_life.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:18:38 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:39:41 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// IN EXECUTE01, YOU CAN FIND THE CHILD PROCESSES AND THE PARENT :)

static int	pickup_kids(t_children *kids)
{
	int			status;
	int			exit_code;
	t_children	*next;

	exit_code = 0;
	status = 0;
	while (kids)
	{
		waitpid(kids->id, &status, 0);
		next = kids->next;
		free(kids);
		kids = next;
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = WTERMSIG(status) + 128;
	return (exit_code);
}

static void	parent(t_cmd cmd, int *writep, int *readp, int cmd_no)
{
	if (cmd_no != 0)
		close(readp[READ]);
	if (cmd_no != cmd.cmd_count - 1)
		close (writep[WRITE]);
}

static pid_t	create_child(t_cmd *cmd, int *writep, int *readp, int cmd_no)
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
		parent(*cmd, writep, readp, cmd_no);
		return (child_id);
	}
}

int	family_life(t_cmd *cmd)
{
	int			pfd[2][2];
	int			i;
	t_children	*kids;
	pid_t		id;

	i = 0;
	kids = NULL;
	while (i < cmd->cmd_count)
	{
		if (i != cmd->cmd_count - 1 || cmd->cmd_count == 2)
		{
			if (pipe(pfd[i % 2]) == -1)
				ft_putstr_fd("pipe error", STDERR_FILENO);
		}
		id = create_child(cmd, pfd[i % 2], pfd[(i + 1) % 2], i);
		if (id == -1)
			return (-1);
		if (kids == NULL)
			kids = new_child(id);
		else
			child_add_back(kids, new_child(id));
		i++;
	}
	return (pickup_kids(kids));
}
