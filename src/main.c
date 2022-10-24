/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:34:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 17:17:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "heredoc/heredoc.h"
#include "substitutor/substitutor.h"

int	minishell(t_cmd *cmd, char **input, char **line)
{
	char	*retstr;

	retstr = NULL;
	if (*input == NULL)
		*line = prompt(cmd);
	else
		*line = *input;
	if (ft_strlen(*line) == 0 || tokenize(cmd, *line) == -1 \
	|| cmd->tokens == NULL || heredoc(cmd, &retstr))
		return (1);
	if (retstr != NULL)
	{
		reset(cmd, *line);
		*input = retstr;
		return (2);
	}
	if (parse(cmd) != 0)
		return (1);
	g_errno = execute(cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;
	char	*line;
	int		to_exit;

	(void)argv;
	input = NULL;
	to_exit = 0;
	if (argc >= 2 && ft_strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'c')
	{
		input = ft_strdup(argv[2]);
		to_exit = 1;
	}
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
		if(to_exit)
			break;
	}
	return (EXIT_SUCCESS);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
