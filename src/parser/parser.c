/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:14 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 18:36:56 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_bin(t_cmd *cmd, t_simple *simple)
{
	char	*myexec;
	int		i;

	if (!simple || !simple->argv || !cmd)
		return ;
	if (ft_strchr(simple->argv[0], '/') != NULL || access(simple->argv[0], X_OK) == 0)
	{
		simple->bin = ft_strdup(simple->argv[0]);
		if (access(simple->bin, X_OK) == -1)
			errno = 2;
		return ;
	}
	i = 0;
	while (cmd->paths && cmd->paths[i])
	{
		myexec = ft_strjoin3(cmd->paths[i++], "/", simple->argv[0]);
		if (!myexec)
			return ;
		if (access(myexec, X_OK) == 0)
		{
			errno = 0;
			simple->bin = myexec;
			return ;
		}
		free (myexec);
	}
	return ;
}

static int	count_cmd(t_cmd *cmd)
{
	int			cmd_count;
	t_simple	*simples;

	cmd_count = 0;
	simples = cmd->simples;
	while (simples != NULL)
	{
		cmd_count++;
		simples = simples->next;
	}
	return (cmd_count);
}

static int	add_data(t_token *token, t_cmd *cmd, t_simple *simple)
{
	int	type;

	type = token->type;
	if (type == GREAT)
		add_outfile(cmd, 0, token->data);
	if (type == LESS)
		add_infile(cmd, token->data);
	if (type == GREATGREAT)
		add_outfile(cmd, 1, token->data);
	if (type == LESSLESS)
		add_delimiter(cmd, token->data);
	if (type == WORD)
		add_arg(simple, token->data);
	if (type == QUOT || type == DQUOT)
		add_arg(simple, token->data);
	if (type == DOLL || type == DOLLQ)
		add_arg(simple, token->data);
	return (0);
}

int	parse(t_token *tokens, t_cmd *cmd)
{
	t_simple	*simple;

	simple = new_simple(0, NULL);
	if (simple == NULL)
		return (-1);
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
		{
			if (simple->argv == NULL)
			{
				g_errno = -1;
				return (-1);
			}
			set_bin(cmd, simple);
			simple_add_back(&cmd->simples, simple);
			simple = new_simple(0, NULL);
			if (simple == NULL)
				return (-1);
		}
		else
			add_data(tokens, cmd, simple);
		tokens = tokens->next;
	}
	if (simple->argv == NULL)
	{
		g_errno = -1;
		return (-1);
	}
	simple_add_back(&cmd->simples, simple);
	set_bin(cmd, simple);
	cmd->cmd_count = count_cmd(cmd);
	return (0);
}
