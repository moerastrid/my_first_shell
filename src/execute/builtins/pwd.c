/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:03:13 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_pwd(t_cmd cmd)
{
	char	buf[10000];

	ft_putstr_fd("buildin pwd is executed\n", STDERR_FILENO);
	ft_putstr_fd(getcwd(buf, 10000), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}
