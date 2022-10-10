/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 23:10:40 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	redirect_infile(t_str_list *infiles)
{
	int	fd;

	if (!infiles)
		return ;
	while (infiles->next)
		infiles = infiles->next;
	fd = open(infiles->str, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_outfile(t_str_list *outfiles)
{
	int	fd;
	int	flags;

	if (outfiles == NULL)
		return ;
	while (outfiles != NULL)
	{
		fd = open(outfiles->str, O_CREAT, 0666);
		close(fd);
		if (outfiles->next == NULL)
			break ;
		outfiles = outfiles->next;
	}
	if (outfiles->append_mode)
		flags = O_RDWR | O_APPEND;
	else
		flags = O_WRONLY;
	fd = open(outfiles->str, flags, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
