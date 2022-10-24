/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 22:16:11 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 20:35:50 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	catch_errno(void)
{
	if (g_errno == 130)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	else if (g_errno == 131)
		ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
	//else if (errno != 0)
	//{
	//	ft_putstr_fd("minishell: ", STDERR_FILENO);
	//	ft_putnbr_fd(errno, STDERR_FILENO);
	//	ft_putstr_fd(" : ", STDERR_FILENO);
	//	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	//	ft_putstr_fd("\n", STDERR_FILENO);
	//}
}
