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

int	parse(t_token *tokens, t_cmd *cmd, char **envp)
{
	int			amount_cmd;
	t_simple	*simple;
	t_path		*path;
	char		**split;

	amount_cmd = 0;
	path = split_path(envp);
	if (tokens == NULL) // No special characters present in string. No redirections, no pipes, no substitutions. Just one simple command.
	{
		simple = ft_calloc(1, sizeof(t_simple));
		if (simple == NULL)
			return (1);
		simple->next = NULL;
		cmd->amount_cmd = 1;
		simple->bin = "";
		simple->argv = NULL;
		cmd->simples = simple;
		return (0);
	}

	// hier komt meer , maar nu voor testen even dit geteld :)
	amount_cmd = count_cmd(cmd);
	cmd->amount_cmd = amount_cmd;



	//check_fds();
	//setup_cmd_lst();
	//replace_def_arg();
	return (0);
}

