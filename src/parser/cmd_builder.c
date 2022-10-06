#include "../../minishell.h"

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