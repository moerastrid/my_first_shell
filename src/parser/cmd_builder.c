#include "parser.h"

int	add_outfile(t_cmd *cmd, int append_mode, char *data)
{
	if (data == NULL)
		return (-1);
	if (cmd->outfiles == NULL)
		cmd->outfiles = str_list_new(data, append_mode);
	else
		str_list_add_back(cmd->outfiles, str_list_new(data, append_mode));
	return (0);
}

int	add_infile(t_cmd *cmd, int append_mode, char *data)
{
	if (data == NULL)
		return (-1);
	if (cmd->infiles == NULL)
		cmd->infiles = str_list_new(data, append_mode);
	else
		str_list_add_back(cmd->infiles, str_list_new(data, append_mode));
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

int add_pipe(t_cmd *cmd)
{
	t_simple *new;

	new = new_simple(0, NULL);
	if (simple_tail(cmd->simples)->argv == NULL)
	{
		g_errno = -1;
		return (-1);
	}
	simple_add_back(&cmd->simples, new);
	return (0);
}
