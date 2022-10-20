/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 16:49:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


typedef struct s_doc {
	char	*name;
	int		no;
}	t_doc;

void	redirect_infile(t_str_list *infiles)
{
	int		fd;
	t_doc	heredoc;

	heredoc = NULL;
	if (infiles == NULL)
		return ;
	while (infiles->next)
	{
		if (infiles->append_mode == 1)
			add_to_heredoc(heredoc);
		infiles = infiles->next;
	}
	if ()
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
