/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 20:58:08 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_pwd()
{
	char	*retstr;

	retstr = getcwd(NULL, 0);
	ft_putstr_fd(retstr, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free (retstr);
	return (0);
}
