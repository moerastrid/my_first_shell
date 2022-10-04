#include "../../minishell.h"

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

void add_outfile(t_cmd *cmd, int append_mode, char *data)
{
	if (cmd->outfiles == NULL)
		cmd->outfiles = str_list_new(data, append_mode);
	else
		str_list_add_back(cmd->outfiles, str_list_new(data, append_mode));
}

void add_infile(t_cmd *cmd, char *data)
{
	if (cmd->infiles == NULL)
		cmd->infiles = str_list_new(data, -1);
	else
		str_list_add_back(cmd->infiles, str_list_new(data, -1));
}

void add_delimiter(t_cmd *cmd, char *data)
{
	if (cmd->delimiters == NULL)
		cmd->delimiters = str_list_new(data, -1);
	else
		str_list_add_back(cmd->delimiters, str_list_new(data, -1));
}

int add_arg(t_simple *simple, char *arg)
{
	char	**argv;
	int		i;

	i = 0;
	if (simple->argv == NULL)
	{
		argv = ft_calloc(sizeof(char *), 2);
		if (argv == NULL)
			return (-1);
		argv[i++] = ft_strdup(arg);
		argv[i] = NULL;
	}
	else
	{
		argv = ft_calloc(sizeof(char *), (simple->argc + 2));
		if (argv == NULL)
			return (-1);
		while (i < simple->argc)
		{
			argv[i] = simple->argv[i];
			i++;
		}
		argv[i++] = ft_strdup(arg);
		argv[i] = NULL;
		free(simple->argv);
	}
	simple->argv = argv;
	simple->argc = i;
	return (0);
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
		if (type == WORD || type == QUOT || type == DQUOT ||
			type == DOLL || type == DOLLQ)
			add_arg(simple, tokens->data);
		if (type == PIPE)
		{
			simple_add_back(&cmd->simples, simple);
			set_bin(cmd, simple);
			simple = new_simple(0, NULL);
		}
		tokens = tokens->next;
	}
	simple_add_back(&cmd->simples, simple);
	if (set_bin(cmd, simple) == -1)
		return (-1);
	cmd->cmd_count = count_cmd(cmd);
	return (0);
}
