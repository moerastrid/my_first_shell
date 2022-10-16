/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:37:19 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 18:14:23 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Reset for next loop.
void	reset_cmd(t_cmd *cmd)
{
	free_simples(cmd->simples);
	free_str_list(cmd->outfiles);
	free_str_list(cmd->infiles);
	free_str_list(cmd->delimiters);
	free_token_list(cmd->tokens);
	free(cmd->paths);
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;
	cmd->tokens = NULL;
	cmd->paths = NULL;
}

// Clear command for exit.
void	clear_cmd(t_cmd *cmd)
{
	reset_cmd(cmd);
}

void	reset(t_cmd *cmd, char *line)
{
	catch_errno(g_errno);
	g_errno = 0;
	clear_cmd(cmd);
	catch_signals();
	free(line);
}
