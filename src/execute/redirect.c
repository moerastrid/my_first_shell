/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:20:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 19:47:31 by ageels        ########   odam.nl         */
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
	char		*lastname;
	t_doc		*heredoc;
	t_str_list	*last_infile;
	int			heredoc_count;

	if (infiles == NULL)
		return ;
	last_infile = infiles;
	heredoc = NULL;
	heredoc_count = 0;
	while (infiles != NULL)
	{
		if (infiles->append_mode == 1)
			docadd_back(&heredoc, docnew(infiles->str, heredoc_count++));
		if (infiles->next == NULL)
			last_infile = infiles;
		infiles = infiles->next;
	}
	if (heredoc_count != 0)
		lastname = heredoc_loop(heredoc);
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
		fd = open(lastname, O_RDONLY, 0664);
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(lastname);
	}
//	if (heredoc_count != 0)
//		reset_heredoc(heredoc);
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

//void	redirect_infile(t_str_list *infiles)
//{
//	int		fd;
//	int		heredoccount;
//	char	*heredocfile;

//	fd = 0;
//	heredoccount = 0;
//	if (!infiles)
//		return ;
//	//while (infiles->next)
//	//{
//	//	if (infiles->append_mode == 1)
//	//		heredoccount++;
//	//	infiles = infiles->next;
//	//}
//	if (infiles->append_mode == 1)
//	{
//		heredocfile = heredoc_loop(infiles->str);
//		fd = open(heredocfile, O_CREAT | O_RDWR, 0664);
//		dup2(fd, STDIN_FILENO);
//		close(fd);
//		unlink(heredocfile);
//		//return ;
//	}
//	else if (infiles->append_mode == 0)
//	{
//		fd = open(infiles->str, O_RDONLY);
//		dup2(fd, STDIN_FILENO);
//		close(fd);
//	}
//}

//typedef struct s_doc {
//	char	*name;
//	int		no;
//}	t_doc;

//void	redirect_infile(t_str_list *infiles)
//{
//	int		fd;
//	t_doc	heredoc;

//	heredoc = NULL;
//	if (infiles == NULL)
//		return ;
//	while (infiles->next) //Skips to last infile.
//	{
//		if (infiles->append_mode == 1)
//			add_to_heredoc(heredoc);
//		infiles = infiles->next;
//	}
//<<<<<<< HEAD
//	if ()
//=======
//	if (infiles->append_mode == 1)
//	{
//		heredocfile = heredoc_loop(infiles->str);
// Hier heb je vanwege de loop hierboven alleen maar 
// toegang tot de laatste infile
//		fd = open(heredocfile, O_CREAT | O_RDWR, 0664);
//		dup2(fd, STDIN_FILENO);
//		close(fd);
//		unlink(heredocfile);
//		return ;
//	}
//	else if (infiles->append_mode == 0)
//	{
//		if(access(infiles->str, R_OK) != 0)
//		{
//			perror(infiles->str); //Prints the correct error, except for "bash:"
//			exit(errno);
//		}
//		fd = open(infiles->str, O_RDONLY);
//		dup2(fd, STDIN_FILENO);
//		close(fd);
//	}
//>>>>>>> a9c5c043dd9c9ada7c21432fb0706b9dc12c430d
//}