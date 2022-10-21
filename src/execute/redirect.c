/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 15:29:49 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

//char	*heredoc_loop(char *eof)
//{
//	char	*line;
//	char	*filename;
//	int		fd;

//	fd = 0;
//	filename = NULL;
//	filename = ft_strdup("heredob");
//	filename = nextfilename(filename);
//	fd = open(filename, O_CREAT | O_RDWR, 0664);
//	dprintf(2, "fd: %d\n", fd);
//	while (1)
//	{
//		line = readline(" > ");
//		if (!line)
//			exit (0);
//		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
//		{
//			close (fd);
//			return (filename);
//		}
//		write(fd, line, ft_strlen(line));
//		write(fd, "\n", ft_strlen("\n"));
//		free(line);
//	}
//}

void	redirect_infile(t_str_list *infiles)
{
	int			fd;
	t_str_list	*last_infile;

	if (infiles == NULL)
		return ;
	last_infile = infiles;
	while (infiles != NULL)
	{
		if (infiles->next == NULL)
			last_infile = infiles;
		infiles = infiles->next;
	}
	if (last_infile->append_mode == 0)
	{
		if (access(last_infile->str, R_OK) != 0)
		{
			perror(last_infile->str);
			exit(errno);
		}
		fd = open(infiles->str, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (last_infile->append_mode == 1)
	{
		fd = open(last_infile->str, O_RDONLY, 0664);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
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
