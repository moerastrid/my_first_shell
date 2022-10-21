/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 16:23:31 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	set_infile(t_str_list *last_infile)
{
	int			fd;

	fd = 0;
	if (last_infile->append_mode == 0)
	{
		if (access(last_infile->str, R_OK) != 0)
		{
			perror(last_infile->str);
			exit(errno);
		}
		fd = open(last_infile->str, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (last_infile->append_mode == 1)
	{
		fd = open(last_infile->str, O_RDONLY, 0664);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(last_infile->str);
	}
}

void	redirect_infile(t_str_list *infiles)
{
	t_str_list	*last_infile;

	if (infiles == NULL)
		return ;
	last_infile = infiles;
	while (infiles != NULL)
	{
		if (infiles->next == NULL)
			last_infile = infiles;
		else if (infiles->append_mode == 1)
			unlink(infiles->str);
		infiles = infiles->next;
	}
	set_infile(last_infile);
}

void	redirect_outfile(t_str_list *outfiles)
{
	int	fd;
	int	flags;

	if (outfiles == NULL)
		return ;
	while (outfiles->next != NULL)
	{
		close(open(outfiles->str, O_CREAT, 0664));
		g_errno = errno;
		outfiles = outfiles->next;
	}
	if (outfiles->append_mode)
		flags = O_RDWR | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(outfiles->str, flags, 0664);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
