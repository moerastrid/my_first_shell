/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 22:16:11 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:01:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	catch_errno(void)
{
	if (g_errno == 130)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	else if (g_errno == 131)
		ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
}
