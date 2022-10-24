#include "substitutor.h"
#include "../heredoc/heredoc.h"
#include "../../lib/gnl/get_next_line.h"

//int	check_heredoc_for_substitution(t_doc *doc)
//{
//	char	*line;
//	int		fd;
//	int		ret;
//	char	*ptr;

//	ret = false;
//	fd = doc->fd;
//	close(fd);
//	fd = open(doc->name, O_RDONLY);
//	if (fd == -1)
//	{
//		perror(doc->name);
//		return (ret);
//	}
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (line == NULL)
//			break ;
//		ptr = ft_strchr(line, '$');
//		if (ptr == NULL)
//		{
//			free(line);
//			continue ;
//		}
//		else if (ft_strlen(ptr) > 1 && ft_isalpha(*(ptr + 1)))
//		{
//			ret = true;
//			close(fd);
//			free(line);
//			return (ret);
//		}
//		free(line);
//	}
//	close(fd);
//	return (ret);
//}

char	*substitute_line(char *line, char **envp)
{
	char	*ptr;
	int		pre_sub_len;
	char	*new_line;

	ptr = line;
	while (ptr && *ptr != '\0')
	{
		while (*ptr != '$' && *ptr != '\0')
			ptr++;
		if (*ptr == '\0')
			break ;
		new_line = replace_once(ptr, line, &pre_sub_len, envp);
		free(line);
		line = new_line;
		ptr = line + pre_sub_len;
	}
	return (line);
}

//int	substitute_heredoc(t_doc **docs, char **envp)
//{
//	int	fd;
//	int	new_fd;
//	char	*new_name;
//	char	*line;
//	t_doc	*doc;

//	doc = *docs;
//	fd = doc->fd;
//	close(fd);
//	fd = open(doc->name, O_RDONLY);
//	if (fd == -1)
//	{
//		perror(doc->name);
//		return (-1);
//	}
//	new_name = ft_strjoin(doc->name, "_42cpy");
//	new_fd = open(new_name, O_CREAT | O_WRONLY | O_APPEND, 0664);
//	if (new_fd == -1)
//	{
//		close(fd);
//		perror(new_name);
//		return (-1);
//	}
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (line == NULL)
//			break ;
//		line = substitute_line(line, envp);
//		ft_putstr_fd(line, new_fd);
//		free(line);
//	}
//	free(new_name);
//	return(0);
//}
