/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 13:35:34 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE.C IS THE EXECUTE MAIN

int	execute(t_cmd *cmd)
{
	int	ret_val;

	ret_val = 0;
	ignore_signals();
	if (cmd->cmd_count <= 0)
		return (1);
	if (cmd->cmd_count == 1)
	{
		if (is_builtin(cmd->simples->argv[0]) == 1)
		{
			redirect_infile(cmd->simples->infiles);
			redirect_outfile(cmd->simples->outfiles);
			ret_val = exec_builtin(cmd->simples, cmd);
			dup2(0, STDOUT_FILENO);
			dup2(1, STDIN_FILENO);
			return (ret_val);
		}
		return (only_child(cmd));
	}
	else
		return (family_life(cmd));
}
