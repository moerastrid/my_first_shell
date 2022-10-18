#include "parser.h"

int	add_arg(t_cmd *cmd, char *arg);

static int	add_stuff(t_cmd *cmd, char *data, int space_flag)
{
	if(space_flag != 0 || simple_tail(cmd->simples)->argv == NULL)
		add_arg(cmd, data);
	else
		add_to_last_arg(cmd, data);
	return (0);
}

static int	add_data(t_cmd *cmd, t_token *token, int space_flag)
{
	int	type;

	type = token->type;
	if (type == GREAT)
		return (simple_add_outfile(cmd, 0, token->data));
	if (type == LESS)
		return (simple_add_infile(cmd, 0, token->data));
	if (type == GREATGREAT)
		return (simple_add_outfile(cmd, 1, token->data));
	if (type == LESSLESS)
		return (simple_add_infile(cmd, 1, token->data));
	if (type == WORD)
		return (add_stuff(cmd, token->data, space_flag));
	if (type == QUOT || type == DQUOT)
		return (add_stuff(cmd, token->data, space_flag));
	if (type == DOLL || type == DOLLQ)
		return (add_stuff(cmd, token->data, space_flag));
	if (type == PIPE)
		return (cmd_add_pipe(cmd));
	return (0);
}

int	parse(t_cmd *cmd)
{
	t_token		*token;
	int			space_flag;
	int			ret;
	t_simple	*tail;

	cmd->simples = new_simple(0, NULL);
	token = cmd->tokens;
	space_flag = 0;
	while (token != NULL)
	{
		ret = add_data(cmd, token, space_flag);
		if (ret != 0)
			return (ret);
		space_flag = token->type == WSPACE;
		token = token->next;
	}
	cmd->cmd_count = count_simples(cmd);
	tail = simple_tail(cmd->simples);
	if (tail->argv == NULL)
		return (-1);
	return (0);
}
