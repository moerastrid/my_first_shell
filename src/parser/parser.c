/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:19:27 by ageels            #+#    #+#             */
/*   Updated: 2022/09/29 17:23:43 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_cmd(t_cmd *cmd)
{
	int			cmd_count;
	t_simple	*simples;

	simples = cmd->simples;
	cmd_count = 1;
	while (simples != NULL)
	{
		cmd_count++;
		simples = simples->next;
	}
	return (cmd_count);
}

int	parse(t_token *tokens, t_cmd *cmd, t_path *path)
{
	int			cmd_count;
	int			type;
	t_simple	*simple;
	char		**argv;

	cmd_count = count_cmd(cmd);
	cmd->cmd_count = cmd_count;
	while (tokens != NULL)
	{
		type = tokens->type;
		if (type == GREAT)
		{
			if(cmd->outfile != NULL)
				free(cmd->outfile);
			// cmd->outfile = ft_strdup(tokens->data);
			// cmd->append_mode = 0;
		}
		if (type == LESS)
		{
			if(cmd->infile != NULL)
				free(cmd->infile);
			// cmd->infile = ft_strdup(tokens->data);
		}
		if (type == GREATGREAT)
		{
			if (cmd->outfile != NULL)
				free(cmd->outfile);
			// cmd->outfile = ft_strdup(tokens->data);
			// cmd->append_mode = 1;
		}
		if (type == LESSLESS)
			// cmd->delimiter = ft_strdup(tokens->data);
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
