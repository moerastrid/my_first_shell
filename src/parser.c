/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:20:57 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/27 19:42:27 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse(char *input, t_cmd *cmd, char **envp)
{
	t_simple	*simple;
	t_token		*tokens;
	t_path		*path;

	tokens = tokenize(input);
	path = split_path(envp);

	if (tokens == NULL) // No special characters present in string. No redirections, no pipes, no substitutions. Just one simple command.
	{
		simple = ft_calloc(1, sizeof(t_simple));
		if (simple == NULL)
			return (1);
		cmd->infile = NULL;
		cmd->outfile = NULL;
		cmd->errfile = NULL;
		cmd->amount_cmd = 1;
		simple->bin = "";
	}

	//check_fds();
	//setup_cmd_lst();
	//replace_def_arg();
	return (0);
}

