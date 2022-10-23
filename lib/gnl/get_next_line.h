#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# if BUFFER_SIZE > INT_MAX
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

char	*do_read(int fd, char *buf, char *storage, ssize_t *stored);
char	*get_next_line(int fd);
char	*ft_strjoin_free(char const *s1, char const *s2);
char	*take_line_from_buffer(char *buf);
size_t	ft_strlen(const char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_bzero(void *s, size_t n);

#endif