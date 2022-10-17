/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 14:46:07 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_cd(void)
{
	char *path;
	char *prevp;
	char *end;

	prevp = NULL;
	end = NULL;
	ft_putstr_fd("buildin is executed\n", 1);
	prevp = ft_strdup(getcwd(NULL, 0));
	end = ft_strrchr(prevp, '/');
	ft_bzero(end, ft_strlen(end));
	path = ft_strdup(prevp);
	free(prevp);
	if (chdir(path) != 0)
		g_errno = errno;
	return (0);
}
