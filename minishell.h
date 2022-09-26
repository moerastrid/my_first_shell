/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:20:14 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 20:05:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>

# define READ 0
# define WRITE 1

//STRUCTS:
typedef struct s_simple {
	char	**argument;
}		t_simple;

typedef struct s_cmd {
	int			amount_cmd;
	t_simple	**simple;
	char		*outfile;
	char		*infile;
	char		*errfile;
}		t_cmd;

// FILES & FUNCTIONS:
//prompt
int	prompt(void);

//parser
int		parse(int argc, char **argv);

//thefam
int		family_life(t_cmd cmds);
int		parent(int *children, t_cmd cmds, int *pfd);
int		child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no);

//buildins (00)
void	bi_echo(void);
void	bi_cd(void);
void	bi_pwd(void);
void	bi_export(void);
void	bi_unset(void);
void	bi_env(void);
void	bi_exit(void);

//execute (00)
void	exec_cmd(t_cmd cmds, int cmd_no);

//utils (00)
size_t	ft_strlen(const char *string);
int		ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
