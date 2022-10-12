/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:37:19 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/12 16:53:55 by ageels        ########   odam.nl         */
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
}

void	reset(t_cmd *cmd, t_children *kids, t_token *tokens)
{
	kill_children(kids);
	free_children(kids);
	g_children = NULL;
	clear_cmd(cmd);
	free_token_list(tokens);
}
