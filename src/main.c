/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:34:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 14:57:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "substitutor/substitutor.h"

int	minishell(t_cmd *cmd, char **input, char **line)
{
	char	*retstr;
	int		err;

	err = 0;
	retstr = NULL;
	if (*input == NULL)
		*line = prompt(cmd);
	else
		*line = ft_strdup(*input);
	if (ft_strlen(*line) == 0 || tokenize(cmd, *line) == -1 \
	|| cmd->tokens == NULL)
		return (1);
	print_tokens(cmd->tokens);
	if (heredoc(cmd, &retstr))
		return (1);
	if (retstr != NULL)
	{
		reset(cmd, *line);
		*input = retstr;
		return (2);
	}
	if (parse(cmd) != 0)
		return (1);
	cmd_simples_set_bin(cmd);
	g_errno = execute(cmd);
	return (1);
}

#include "heredoc/heredoc.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;
	char	*line;

	//atexit(run_leaks);
	(void)argv;
	input = NULL;
	line = NULL;
	if (setup(&cmd, envp, argc) == -1)
		return (-1);
	while (1)
	{
		if (minishell(&cmd, &input, &line) == 1)
		{
			input = NULL;
			reset(&cmd, line);
		}
	}
	return (EXIT_SUCCESS);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
