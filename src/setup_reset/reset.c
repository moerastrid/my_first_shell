/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:37:19 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 22:45:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
# include "../env/env.h"

// Reset for next loop.
void	reset_cmd(t_cmd *cmd)
{
	free_simples(cmd->simples);
	free_token_list(cmd->tokens);
	if(cmd->paths)
		free(cmd->paths);
	cmd->simples = NULL;
	cmd->tokens = NULL;
	cmd->paths = NULL;
}

// Clear command for exit.
void	clear_cmd(t_cmd *cmd)
{
	free_envc(cmd->envc);
	reset_cmd(cmd);
}

void	reset(t_cmd *cmd, char *line)
{
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
	catch_errno(g_errno);
	// g_errno = 0;
	reset_cmd(cmd);
	catch_signals();
	free(line);
}
