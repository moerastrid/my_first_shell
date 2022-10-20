#include "parser.h"

// TESTS ALL TOKENS:
// word >out.txt <in.txt >>out.txt <<in "$SHLVL" $SHLVL 'hi' $? |

static int add_to_argv(int space, t_cmd *cmd, t_token **tokens)
{
	if (simple_tail(cmd->simples)->argv == NULL || space == 1)
		return (add_arg(cmd, (*tokens)->data));
	else
		return (add_to_last_arg(cmd, (*tokens)->data));
}

static int	parse_words(t_cmd *cmd, t_token **tokens)
{
	int	type;
	int spaced;

	spaced = 0;
	while (1)
	{
		if ((*tokens) == NULL)
			return (0);
		type = (*tokens)->type;
		if (type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		{
			add_to_argv(1, cmd, tokens);
			return (0);
			*tokens = (*tokens)->next;
			spaced = 0;
		}
		else if (type & WSPACE)
		{
			*tokens = (*tokens)->next;
			spaced = 1;
		}
		else
			return (0);
	}
	return (0);
}

static int	parse_token(t_cmd *cmd, t_token **token)
{
	int	type;
	(void)parse_words;

	type = (*token)->type;
	if (type & (GREAT + LESS + GREATGREAT + LESSLESS))
		return (parse_redirect(cmd, token));
	if (type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		return (add_to_argv(1, cmd, token));
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
		ret = parse_token(cmd, &token);
		if (ret != 0)
			return (ret);
		if (token == NULL)
			break;
		token = token->next;
	}
	cmd->cmd_count = count_simples(cmd);
	tail = simple_tail(cmd->simples);
	if (tail->argv == NULL)
		return (-1);
	return (0);
}
