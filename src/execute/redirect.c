/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 20:28:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	set_infile(t_str_list *infile)
{
	int	fd;

	fd = 0;
	if (infile->append_mode == 0)
	{
		if (access(infile->str, R_OK) != 0)
		{
			perror(infile->str);
			return (errno);
		}
		fd = open(infile->str, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (infile->append_mode == 1)
	{
		fd = open(infile->str, O_RDONLY, 0664);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(infile->str);
	}
	return (0);
}

static int	create_outfiles(t_str_list *outfiles)
{
	int	fd;

	while (outfiles != NULL)
	{
		fd = open(outfiles->str, O_CREAT | O_TRUNC, 0664);
		if (fd != -1)
			close(fd);
		else
		{
			perror(outfiles->str);
			return (errno);
		}
		outfiles = outfiles->next;
	}
	return (0);
}

static void	unlink_heredocs(t_str_list *infiles)
{
	while (infiles->next != NULL)
	{
		if (infiles->append_mode == 1)
			unlink(infiles->str);
		infiles = infiles->next;
	}
}

int	redirect_infile(t_str_list *infiles)
{
	int	ret;

	if (infiles == NULL)
		return (0);
	unlink_heredocs(infiles);
	ret = infile_check_access(infiles);
	if (ret != 0)
		return (ret);
	return (set_infile(str_list_tail(infiles)));
}

int	redirect_outfile(t_str_list *outfiles)
{
	int	fd;
	int	flags;
	int	ret;

	if (outfiles == NULL)
		return (0);
	ret = create_outfiles(outfiles);
	if (ret != 0)
		return (errno);
	outfiles = str_list_tail(outfiles);
	if (outfiles->append_mode)
		flags = O_WRONLY | O_APPEND;
	else
		flags = O_WRONLY | O_TRUNC;
	fd = open(outfiles->str, flags, 0664);
	if (fd == -1)
	{
		perror(outfiles->str);
		return (errno);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
