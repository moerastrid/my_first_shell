/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 16:42:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE.C IS THE EXECUTE MAIN

int	execute(t_cmd *cmd)
{
	int	ret;
	int	fd_out_copy;

	fd_out_copy = dup(STDOUT_FILENO);
	ignore_signals();
	if (cmd->cmd_count <= 0)
		return (1);
	if (cmd->cmd_count == 1)
	{
		if (is_builtin(cmd->simples->argv[0]) == 1)
		{
			ret = redirect_outfile(cmd->simples->outfiles);
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
