#include "parser.h"

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

int	parse(t_token *tokens, t_cmd *cmd)
{
	t_simple	*simple;
	int			type;

	simple = new_simple(0, NULL);
	while (tokens != NULL)
	{
		type = tokens->type;
		if (type == GREAT)
			add_outfile(cmd, 0, tokens->data);
		if (type == LESS)
			add_infile(cmd, tokens->data);
		if (type == GREATGREAT)
			add_outfile(cmd, 1, tokens->data);
		if (type == LESSLESS)
			add_delimiter(cmd, tokens->data);
		if (type == WORD)
			add_arg(simple, tokens->data);
		if (type == QUOT || type == DQUOT)
			add_arg(simple, tokens->data);
		if (type == DOLL || type == DOLLQ)
			add_arg(simple, tokens->data);
		if (type == PIPE)
		{
			if (simple->argv == NULL)
			{
				printf("%s\n", "Parse error");
				return (-1);
			}
			set_bin(cmd, simple);
			simple_add_back(&cmd->simples, simple);
			simple = new_simple(0, NULL);
		}
		tokens = tokens->next;
	}
	if(simple->argv == NULL)
	{
		printf("%s\n", "Parse error");
		// free & reset alles hiervoor
		return (-1);
	}
	simple_add_back(&cmd->simples, simple);
	if (set_bin(cmd, simple) == -1)
		return (-1);
	cmd->cmd_count = count_cmd(cmd);
	return (0);
}
