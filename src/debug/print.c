/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 16:35:52 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:18:25 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

// Totally illegal
void	print_token_type(enum e_token_type num)
{
	switch (num)
	{
		case WORD:
			printf("%s", "WORD");
		break ;
		case GREAT:
			printf("%s", "GREAT");
		break ;
		case LESS:
			printf("%s", "LESS");
		break ;
		case PIPE:
			printf("%s", "PIPE");
		break ;
		case GREATGREAT:
			printf("%s", "GREATGREAT");
		break ;
		case LESSLESS:
			printf("%s", "LESSLESS");
		break ;
		case DOLL:
			printf("%s", "DOLL");
		break ;
		case DOLLQ:
			printf("%s", "DOLLQ");
		break ;
		case QUOT:
			printf("%s", "QUOT");
		break ;
		case DQUOT:
			printf("%s", "DQUOT");
		break ;
		case WSPACE:
			printf("%s", "WSPACE");
		break ;
	}
}

void	print_tokens(t_token *root)
{
	t_token	*i;

	i = root;
	printf("Token list\t: ");
	while (i != NULL)
	{
		printf("(");
		print_token_type(i->type);
		printf(": '%s')", i->data);
		i = i->next;
		if (i != NULL)
			printf("->");
	}
	printf("\n");
}

void	print_str_list(t_str_list *root, char *name)
{
	if (root != NULL)
		printf("%s: ", name);
	while (root != NULL)
	{
		printf("[%s]", root->str);
		root = root->next;
		if (root != NULL)
			printf("->");
		else
			printf("\n");
	}
}

void	print_simples(t_simple *root)
{
	char		**argv;
	int			i;

	while (root != NULL)
	{
		argv = root->argv;
		printf("Simple: bin     : %s\n", root->bin);
		printf("\targc    : %d\n\targv    : ", root->argc);
		i = 0;
		while (i < root->argc)
		{
			if (i != root->argc - 1)
				printf("[%s]->", argv[i++]);
			else
				printf("[%s]\n", argv[i++]);
		}
		if (root->outfiles)
			printf("\t");
		print_str_list(root->outfiles, "Outfiles");
		if (root->infiles)
			printf("\t");
		print_str_list(root->infiles, "Infiles ");
		root = root->next;
	}
}

void	print_cmd(t_cmd cmd)
{
	printf("%s\n", "=================================");
	printf("%s\n", "\tCommand struct breakdown");
	printf("cmd_count\t: %d\n", cmd.cmd_count);
	print_tokens(cmd.tokens);
	print_simples(cmd.simples);
	printf("%s\t: %d\n", "Env size", count_envp(cmd.envc));
	printf("%s\n", "=================================");
}

void	print_envc(char **envc)
{
	while (envc && *envc)
	{
		printf("%s\n", *envc++);
	}
}

//void print_children(t_children *root)
//{
//	t_children *ptr;

//	ptr = root;
//	if (ptr == NULL)
//		return ;
//	printf("The kids: [");
//	while(ptr != NULL)
//	{
//		if(ptr->next == NULL)
//			printf("%d]\n", ptr->id);
//		else
//			printf("%d->", ptr->id);
//		ptr = ptr->next;
//	}
//}

void	run_leaks(void)
{
	system("leaks minishell");
}

void	run_lsof(void)
{
	system("lsof -c minishell");
}

void	run_cat_fd(void)
{
	system("cat /dev/fd");
}

// #include <sys/syslimits.h>
# define OPEN_MAX 1000
void	close_all(void)
{
	for(int i = 3; i < OPEN_MAX; i++)
	{
		close(i);
	}
}
