/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:37:19 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:16:24 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

void	unlink_docs(t_doc *docs)
{
	while (docs)
	{
		if (access(docs->name, F_OK) == 0)
			unlink(docs->name);
		if (errno == 2)
			errno = 0;
		docs = docs->next;
	}
}

// Reset for next loop.
void	reset_cmd(t_cmd *cmd)
{
	free_simples(cmd->simples);
	unlink_docs(cmd->doc);
	docs_free(cmd->doc);
	free_token_list(cmd->tokens);
	if (cmd->paths)
		free(cmd->paths);
	cmd->simples = NULL;
	cmd->tokens = NULL;
	cmd->paths = NULL;
	cmd->doc = NULL;
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
	catch_errno();
	reset_cmd(cmd);
	catch_signals();
	free(line);
}
