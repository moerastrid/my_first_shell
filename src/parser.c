/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:19:27 by ageels            #+#    #+#             */
/*   Updated: 2022/09/29 16:05:03 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "path.h"

static int	count_cmd(t_cmd *cmd)
{
	int			amount_cmd;
	t_simple	*simples;

	simples = cmd->simples;
	amount_cmd = 1;
	while (simples != NULL)
	{
		amount_cmd++;
		simples = simples->next;
	}
	return (amount_cmd);
}

int	parse(t_token *tokens, t_cmd *cmd, t_path *path)
{
	int			amount_cmd;
	int			type;
	t_simple	*simple;
	char		**argv;

	amount_cmd = count_cmd(cmd);
	cmd->amount_cmd = amount_cmd;
	while (tokens != NULL)
	{
		type = tokens->type;
		if (type == GREAT)
			cmd->outfile = ft_strdup(tokens->data);
		if (type == LESS)
			cmd->infile = ft_strdup(tokens->data);
		if (type == GREATGREAT)
			;
		if (type == LESSLESS)
			cmd->delimiter = ft_strdup(tokens->data);
		if (type == WORD)
		{
			simple = NULL;
		}
		tokens = tokens->next;
	}
	//check_fds();
	//setup_cmd_lst();
	//replace_def_arg();
	return (0);
}
