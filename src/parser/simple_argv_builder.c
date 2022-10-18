#include "parser.h"

int	simple_add_outfile(t_cmd *cmd, t_token *token)
{
	t_simple *simple;

	int append_mode = token->type == GREATGREAT;

	simple = simple_tail(cmd->simples);
	if (token->data == NULL)
		return (-1);
	if (simple->outfiles == NULL)
		simple->outfiles = str_list_new(token->data, append_mode);
	else
		str_list_add_back(simple->outfiles, str_list_new(token->data, append_mode));
	return (0);
}

int	simple_add_infile(t_cmd *cmd, t_token *token)
{
	t_simple *simple;

	int append_mode = token->type == LESSLESS;

	simple = simple_tail(cmd->simples);
	if (token->data == NULL)
		return (-1);
	if (simple->infiles == NULL)
		simple->infiles = str_list_new(token->data, append_mode);
	else
		str_list_add_back(simple->infiles, str_list_new(token->data, append_mode));
	return (0);
}

int	add_arg(t_cmd *cmd, char *arg)
{
	char		**argv;
	t_simple	*tail;
	int			i;

	if (arg == NULL)
		return (-1);
	tail = simple_tail(cmd->simples);
	argv = ft_calloc(sizeof(char **), (tail->argc + 2));
	if (argv == NULL)
		return (-1);
	i = 0;
	while (i < tail->argc)
	{
		argv[i] = tail->argv[i];
		i++;
	}
	if (tail->argv)
		free(tail->argv);
	argv[i++] = ft_strdup(arg);
	tail->argv = argv;
	tail->argc = i;
	return (0);
}

int add_to_last_arg(t_cmd *cmd, char *arg)
{
	t_simple	*tail;
	char		*tail_argv_last;
	int			i;

	if (arg == NULL)
		return (-1);
	tail = simple_tail(cmd->simples);
	if (tail->argv == NULL)
		return (-1);
	i = 0;
	while(tail->argv[i] != NULL)
		i++;
	i--;
	tail_argv_last = tail->argv[i];
	tail->argv[i] = ft_strjoin(tail->argv[i], arg);
	free(tail_argv_last);
	return (0);
}