/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:49:16 by ageels            #+#    #+#             */
/*   Updated: 2022/10/14 18:34:46 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// EXECUTE00 IS THE EXECUTE MAIN

int	execute(t_cmd *cmd, t_token *tokens)
{
	int	ret_val;

	ret_val = 0;
	ignore_signals();
	if (cmd->cmd_count <= 0)
		return (-1);
	if (cmd->cmd_count == 1)
	{
		if (is_builtin(cmd->simples) == 1)
		{
			redirect_infile(cmd->infiles);
			redirect_outfile(cmd->outfiles);
			ret_val = exec_builtin(cmd->simples, cmd, tokens);
			dup2(0, STDIN_FILENO);
			dup2(1, STDOUT_FILENO);
			// system("lsof -c minishell");
			return (ret_val);
		}
		return (only_child(*cmd));
	}
	else
		return (family_life(cmd));
}
