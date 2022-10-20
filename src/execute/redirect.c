/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 23:24:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*nextfilename(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i - 1] = s[i - 1] + 1;
	free(s);
	if (access(ret, F_OK) == 0)
	{
		//if (ft_strncmp(ret, "heredoz", 8))
		//	ret = "plsstoo";
		ret = nextfilename(ret);
	}
	return (ret);
}

char	*heredoc_loop(char *eof)
{
	char	*line;
	char	*filename;
	int		fd;

	fd = 0;
	filename = NULL;
	filename = ft_strdup("heredob");
	filename = nextfilename(filename);
	fd = open(filename, O_CREAT | O_RDWR, 0664);
	dprintf(2, "fd: %d\n", fd);
	while (1)
	{
		line = readline(" > ");
		if (!line)
			exit (0);
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			close (fd);
			return (filename);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", ft_strlen("\n"));
		free(line);
	}
}

void	redirect_infile(t_str_list *infiles)
{
	int		fd;
	int		heredoccount;
	char	*heredocfile;

	fd = 0;
	heredoccount = 0;
	if (!infiles)
		return ;
	while (infiles->next) //Skips to last infile.
	{
		if (infiles->append_mode == 1)
			heredoccount++;
		infiles = infiles->next;
	}
	if (infiles->append_mode == 1)
	{
		heredocfile = heredoc_loop(infiles->str); //Hier heb je vanwege de loop hierboven alleen maar toegang tot de laatste infile.
		fd = open(heredocfile, O_CREAT | O_RDWR, 0664);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(heredocfile);
		return ;
	}
	else if (infiles->append_mode == 0)
	{
		if(access(infiles->str, R_OK) != 0)
		{
			perror(infiles->str); //Prints the correct error, except for "bash:"
			exit(errno);
		}
		fd = open(infiles->str, O_RDONLY);
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
	while (outfiles != NULL)
	{
		fd = open(outfiles->str, O_CREAT, 0664);
		close(fd);
		if (outfiles->next == NULL)
			break ;
		if (outfiles->append_mode == 0)
			close(open(outfiles->str, O_WRONLY | O_CREAT | O_TRUNC, 0664));
		else if (outfiles->append_mode == 1)
			close(open(outfiles->str, O_RDWR | O_APPEND, 0664));
		outfiles = outfiles->next;
	}
	if (outfiles->append_mode)
		flags = O_RDWR | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(outfiles->str, flags, 0664);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
