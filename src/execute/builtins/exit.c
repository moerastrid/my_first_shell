/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/25 00:16:28 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static long long int	ft_atoi_ret(const char *str, int *ret)
{
	int				a;
	long long int	result;
	long long int	mincounter;

	a = 0;
	result = 0;
	mincounter = 1;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			mincounter = mincounter * -1;
		str++;
	}
	while (*str != '\0')
	{
		if (ft_isdigit(*str) != 1)
		{
			*ret = -1;
			return (255);
		}
		result = (result * 10);
		result = (long long)(result + (*str - '0'));
		str++;
	}
	return (result * mincounter);
}

static void	err_ret(int ret, long long int num, t_simple *simple)
{
	if (ret == -1 || num > INT32_MAX || num < INT32_MIN)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(simple->argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_errno = 255;
		exit (g_errno);
	}
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
	//print_cmd(*cmd);
	if (simple->argv && simple->argv[1])
	{
		num = ft_atoi_ret(simple->argv[1], &ret);
		//dprintf(2, "num: %lld\nret: %d\n", num, ret);
		err_ret(ret, num, simple);
		clear_cmd(cmd);
		exit (num);
	}
	clear_cmd(cmd);
	exit (g_errno);
}
