/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute00.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 20:49:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/12 18:44:00 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE00 IS THE EXECUTE MAIN

int	execute(t_cmd cmds, t_token *tokens)
{
	int	ret_val;

	ret_val = 0;
	if (cmds.cmd_count <= 0)
		return (-1);
	if (cmds.cmd_count == 1)
	{
		if (is_builtin(cmds.simples) == 1)
		{
			redirect_infile(cmds.infiles);
			redirect_outfile(cmds.outfiles);
			ret_val = exec_builtin(cmds.simples, cmds, tokens);
			dup2(0, STDIN_FILENO);
			dup2(1, STDOUT_FILENO);
			return (ret_val);
		}
		return (only_child(cmds));
	}
	else
		return (family_life(cmds));
}
