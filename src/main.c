/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:34:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:34:33 by ageels        ########   odam.nl         */
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

	// // Heredoc substitution test.
	// t_doc *doc = docnew("EOF", token_new(NULL, 0));
	// // sleep(10); //time to put $something into the doc manually.
	// char *sysstr = ft_strjoin("echo ' $PATH/a/b ' >> ", doc->name);
	// system(sysstr);
	// if (check_heredoc_for_substitution(doc)) // AND delimiter token is not DQUOT
	// 	substitute_heredoc(doc, envp);
	// free(doc);
	// free(sysstr);
	// return 0;

	// #include "../lib/gnl/get_next_line.h"
	//
	// int fd = open("Makefile", O_RDONLY);
	// char *s1 = get_next_line(fd);
	// printf("%s\n", s1);
	// free(s1);
	// return 0;

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
