#include "parser.h"
void	set_bin(t_cmd *cmd, t_simple *simple)
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

static int	add_word(t_cmd *cmd, char *data)
{
	int			ret;
	t_simple	*tail;

	ret = add_arg(cmd, data);
	tail = simple_tail(cmd->simples);
	if (tail->argc == 1)
		set_bin(cmd, tail);
	return (ret);
}

static int	add_data(t_cmd *cmd, t_token *token)
{
	int	type;

	type = token->type;
	if (type == GREAT)
		return(add_outfile(cmd, 0, token->data));
	if (type == LESS)
		return(add_infile(cmd, token->data));
	if (type == GREATGREAT)
		return(add_outfile(cmd, 1, token->data));
	if (type == LESSLESS)
		return(add_delimiter(cmd, token->data));
	if (type == WORD)
		return(add_word(cmd, token->data));
	if (type == QUOT || type == DQUOT)
		return(add_arg(cmd, token->data));
	if (type == DOLL || type == DOLLQ)
		return(add_arg(cmd, token->data));
	if (token->type == PIPE)
		return(add_pipe(cmd));
	return (0);
}

int	parse(t_cmd *cmd)
{
	t_token		*token;

	cmd->simples = new_simple(0, NULL);
	token = cmd->tokens;
	while (token != NULL)
	{
		add_data(cmd, token);
		token = token->next;
	}
	cmd->cmd_count = count_cmd(cmd);
	return (0);
}
