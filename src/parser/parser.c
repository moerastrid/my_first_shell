#include "../../minishell.h"

static int	count_cmd(t_cmd *cmd)
{
	int			cmd_count;
	t_simple	*simples;

	simples = cmd->simples;
	cmd_count = 1;
	while (simples != NULL)
	{
		cmd_count++;
		simples = simples->next;
	}
	return (cmd_count);
}

void add_outfile(t_cmd *cmd, int append_mode, char *data)
{
	if(cmd->outfiles == NULL)
		cmd->outfiles = str_list_new(data, append_mode);
	else
		str_list_add_back(cmd->outfiles, str_list_new(data, append_mode));
}

void add_infile(t_cmd *cmd, char *data)
{
	if(cmd->infiles == NULL)
		cmd->infiles = str_list_new(data, -1);
	else
		str_list_add_back(cmd->infiles, str_list_new(data, -1));

	// print_str_list(cmd->infiles, 0);
}

void add_delimiter(t_cmd *cmd, char *data)
{
	if(cmd->delimiters == NULL)
		cmd->delimiters = str_list_new(data, -1);
	else
		str_list_add_back(cmd->delimiters, str_list_new(data, -1));
}

int	parse(t_token *tokens, t_cmd *cmd, t_path *path)
{
	int			cmd_count;
	int			type;

	cmd_count = count_cmd(cmd);
	cmd->cmd_count = cmd_count;
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
		{
			//generate simplecommands.
		}
		tokens = tokens->next;
	}
	return (0);
}
