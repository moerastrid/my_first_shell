/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:20:14 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 21:50:42 by ageels        ########   odam.nl         */
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
	char	**arguments;
}	t_simple;

typedef struct s_cmd {
	int			amount_cmd;
	t_simple	**simple;
	char		*outfile;
	char    	*infile;
	char		*errfile;
}	t_cmd;

enum Token_type {
	GREAT = 1,
	LESS = 2,
	PIPE = 3,
	GREATGREAT = 4, //Redirect STDOUT in append mode.
	LESSLESS = 5, //HEREDOC
	DOLL = 6,
	DOLLQ = 7,
};

typedef struct s_token {
	enum Token_type	type;
	char			*data;
	struct s_token	*next;
}	t_token;

// FILES & FUNCTIONS:
//prompt
int	prompt(void);

//Lexer (00, 01)
t_token	*tokenize(char *input);
t_token	*token_new(char *data, int type);
void	token_add_back(t_token* tokens, t_token* new);

//Parser
int		parse(char *input, t_cmd *cmd);

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
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n) ;

#endif
