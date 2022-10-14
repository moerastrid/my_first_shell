/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:37:19 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 13:25:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	clear_cmd(t_cmd *cmd)
{
	free_simples(cmd->simples);
	cmd->simples = NULL;
	free_str_list(cmd->outfiles);
	cmd->outfiles = NULL;
	free_str_list(cmd->infiles);
	cmd->infiles = NULL;
	free_str_list(cmd->delimiters);
	cmd->delimiters = NULL;
	free(cmd->paths);
	cmd->paths = NULL;
}

void	reset(t_cmd *cmd, t_token *tokens)
{
	clear_cmd(cmd);
	free_token_list(tokens);
	catch_signals();
	catch_errno(g_errno);
}
