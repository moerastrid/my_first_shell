/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 14:53:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_pwd(t_cmd cmd)
{
	(void)cmd;
	ft_putstr_fd("executing pwd\n", STDERR_FILENO);
	ft_putstr_fd(getcwd(NULL, 0), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (0);
}
