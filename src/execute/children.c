/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:09:08 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 14:24:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
		;// redirect_infile(cmd.infiles);
	if (cmd_no == cmd.cmd_count - 1)
		;// redirect_outfile(cmd.outfiles);
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

void	child(t_cmd *cmd, int *writep, int *readp, int cmd_no)
{
	int			ret_val;
	t_simple	*simple;

	ret_val = 0;
	close(writep[READ]);
	child_redirect(*cmd, writep, readp, cmd_no);
	simple = get_simple(*cmd, cmd_no);
	if (is_builtin(simple) == 1)
	{
		if (errno == 2)
			errno = 0;
		ret_val = exec_builtin(simple, cmd);
		dup2(0, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
		exit (ret_val);
	}
	else
	{
		redirect_infile(simple->infiles);
		redirect_outfile(simple->outfiles);
		exec_cmd(simple, cmd->envc);
	}
}
