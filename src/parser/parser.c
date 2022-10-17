#include "parser.h"

static int	count_simples(t_cmd *cmd)
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

// Not sure about this one yet..
static int	add_word(t_cmd *cmd, char *data)
{
	int			ret;
	t_simple	*tail;

	ret = add_arg(cmd, data);
	tail = simple_tail(cmd->simples);
	if (tail->argc == 1)
		set_bin(cmd, tail); // Waar moet dit komen te staan?
	return (ret);
}

static int	add_data(t_cmd *cmd, t_token *token)
{
	int	type;

	type = token->type;
	if (type == GREAT)
		return (add_outfile(cmd, 0, token->data));
	if (type == LESS)
		return (add_infile(cmd, token->data));
	if (type == GREATGREAT)
		return (add_outfile(cmd, 1, token->data));
	if (type == LESSLESS)
		return (add_delimiter(cmd, token->data));
	if (type == WORD)
		return (add_word(cmd, token->data));
	if (type == QUOT || type == DQUOT)
		return (add_arg(cmd, token->data));
	if (type == DOLL || type == DOLLQ)
		return (add_arg(cmd, token->data));
	if (token->type == PIPE)
		return (add_pipe(cmd));
	return (0);
}

int	parse(t_cmd *cmd)
{
	t_token		*token;
	int			ret;

	cmd->simples = new_simple(0, NULL);
	token = cmd->tokens;
	while (token != NULL)
	{
		ret = add_data(cmd, token);
		if (ret != 0)
			return (ret);
		token = token->next;
	}
	cmd->cmd_count = count_simples(cmd);
	tail = simple_tail(cmd);
	if (tail.type == 0)
	{
		clear_cmd(cmd);
		return (-1)
	}

	return (0);
}
