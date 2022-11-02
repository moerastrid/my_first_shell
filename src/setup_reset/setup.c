/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:59:54 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/02 15:13:16 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

static void	setup_termios(void)
{
	struct termios	my_term;

	if (tcgetattr(0, &my_term) == -1)
		return ;
	my_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &my_term);
}

static int	setup_cmd(t_cmd *cmd, char **envp)
{
	char	*str;
	char	*num;
	int		lvl;

	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->tokens = NULL;
	cmd->paths = NULL;
	cmd->doc = NULL;
	cmd->err = 0;
	cmd->envc = copy_env(envp);
	str = find_str("SHLVL", cmd->envc) + 6;
	if (str == (void *)0x6)
		return (0);
	lvl = ft_atoi(str) + 1;
	num = ft_itoa(lvl);
	str = ft_strjoin("SHLVL=", num);
	if (str == NULL)
		return (10);
	env_replace("SHLVL", str, cmd->envc);
	free(str);
	free(num);
	return (0);
}

int	setup(t_cmd *cmd, char **envp)
{
	g_errno = 0;
	setup_termios();
	catch_signals();
	return (setup_cmd(cmd, envp));
}

int	check_c_mode(int argc, char **argv, char **input)
{
	if (argc > 2 && ft_strlen(argv[1]) == 2 \
	&& argv[1][0] == '-' && argv[1][1] == 'c')
	{
		*input = ft_strdup(argv[2]);
		return (1);
	}
	else if (argc >= 2)
	{
		ft_putstr_fd("usage: ./minishell [-c arg]\n", STDERR_FILENO);
		return (2);
	}
	return (0);
}
