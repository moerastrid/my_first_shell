/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 20:16:13 by ageels        ########   odam.nl         */
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
		//if (ft_strncmp(ret, "heredoz", 8))
		//	ret = "plsstoo";
		ret = nextfilename(ret);
	return (ret);
}

int	heredoc_loop(char *eof)
{
	char	*line;
	char	*filename;
	int		fd;

	fd = 0;
	filename = NULL;
	filename = ft_strdup("heredob");
	filename = nextfilename(filename);
	fd = open(filename, O_CREAT | O_RDWR);
	dprintf(2, "fd: %d\n", fd);
	while (1)
	{
		line = readline(" > ");
		if (!line)
			exit (0);
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
			return (fd);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", ft_strlen("\n"));
	}
	return (fd);
}

void	redirect_infile(t_str_list *infiles)
{
	int	fd;
	int	heredoccount;

	fd = 0;
	heredoccount = 0;
	if (!infiles)
		return ;
	while (infiles->next)
	{
		if (infiles->append_mode == 1)
			heredoccount++;
		infiles = infiles->next;
	}
	if (infiles->append_mode == 1)
	{
		fd = heredoc_loop(infiles->str);
		dprintf(2, "fd: %d\n", fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return ;
	}
	else if (infiles->append_mode == 0)
	{
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
	{
		return ;
	}
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
