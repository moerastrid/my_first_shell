/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 17:46:43 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE.C IS THE EXECUTE MAIN

int	infile_check_access(t_str_list *infiles)
{
	while (infiles)
	{
		if(access(infiles->str, F_OK) != 0)
		{
			perror(infiles->str);
			return (errno);
		}
		if(access(infiles->str, R_OK) != 0)
		{
			perror(infiles->str);
			return (errno);
		}
		infiles = infiles->next;
	}
	return (0);
}

int	execute(t_cmd *cmd)
{
	int	ret;
	int	fd_out_copy;

	ignore_signals();
	if (cmd->cmd_count <= 0)
		return (1);
	if (cmd->cmd_count == 1)
	{
		if (cmd->simples->argv != NULL && is_builtin(cmd->simples) == 1)
		{
			fd_out_copy = dup(STDOUT_FILENO);
			ret = redirect_outfile(cmd->simples->outfiles);
			ret += infile_check_access(cmd->simples->infiles);
			if (!ret)
				ret += exec_builtin(cmd->simples, cmd);
			dup2(fd_out_copy, STDOUT_FILENO);
			close(fd_out_copy);
			return (ret);
		}
		return (only_child(cmd));
	}
	else
		return (family_life(cmd));
}
