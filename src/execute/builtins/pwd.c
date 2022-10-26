/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:19:06 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	bi_pwd(void)
{
	char	*retstr;

	retstr = getcwd(NULL, 0);
	ft_putstr_fd(retstr, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free (retstr);
	return (0);
}
