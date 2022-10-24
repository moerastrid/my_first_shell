/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 23:51:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

long long int	ft_atoi_ret(const char *str, int *ret)
{
	int	a;
	long long int	result;
	long long int	mincounter;

	a = 0;
	result = 0;
	mincounter = 1;
	if ((str[a] == '+') || (str[a] == '-'))
	{
		if (str[a] == '-')
			mincounter = mincounter * -1;
		a++;
	}
	while (str[a] != '\0')
	{
		if (ft_isdigit(str[a]) != 1)
		{
			*ret = -1;
			g_errno = 255;
			return (0);
		}
		result = (result * 10);
		result = (result + (str[a] - '0'));
		a++;
	}
	return (result * mincounter);
}

void	bi_exit(t_cmd *cmd, t_simple *simple)
{
	int	ret;
	long long int	num;

	ret = 0;
	num = 0;
	if (cmd->cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (simple->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		exit (1);
	}
	if (simple->argv && simple->argv[1])
	{
		num = ft_atoi_ret(simple->argv[1], &ret);
		if (ret == -1 || num > INT16_MAX || num < INT16_MIN)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(simple->argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit (255);
		}
		clear_cmd(cmd);
		exit (num);
	}
	clear_cmd(cmd);
	exit (g_errno);
}
