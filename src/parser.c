/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:27 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:25:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_token *tokens)
{
	int	amount_cmds;

	amount_cmds = 1;
	while (tokens != NULL)
	{
		amount_cmds ++;
		tokens = tokens->next;
	}
	return (amount_cmds);
}

int	parse(char *input, t_cmd *cmds, char **envp)
{
	int			amount_cmd;
	t_simple	*simple;
	t_token		*tokens;
	t_path		*path;

	amount_cmd = 0;
	tokens = NULL;
	//tokens = tokenize(input);
	//path = split_path(envp);

	if (tokens == NULL) // No special characters present in string. No redirections, no pipes, no substitutions. Just one simple command.
	{
		simple = ft_calloc(1, sizeof(t_simple));
		if (simple == NULL)
			return (1);
		amount_cmd = 1;
		cmds->infile = NULL;
		cmds->outfile = NULL;
		cmds->errfile = NULL;
		cmds->amount_cmd = 1;
		simple->bin = "";
	}
	else
	{
		// hier komt meer , maar nu voor testen even dit geteld :)
		amount_cmd = count_cmds(tokens);
	}
	cmds->amount_cmd = amount_cmd;
	//check_fds();
	//setup_cmd_lst();
	//replace_def_arg();
	return (0);
}

