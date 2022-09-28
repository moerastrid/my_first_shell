# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 14:33:40 by tnuyten           #+#    #+#              #
#    Updated: 2021/10/27 16:22:57 by tnuyten          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =				ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_itoa.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_striteri.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c \


BONUS_SRCS =			ft_lstnew.c \
						ft_lstadd_front.c \
						ft_lstsize.c \
						ft_lstlast.c \
						ft_lstadd_back.c \
						ft_lstdelone.c \
						ft_lstclear.c \
						ft_lstmap.c \
						ft_lstiter.c

ifdef	BONUS_ADD
	FILES = $(SRCS) $(BONUS_SRCS)
else
	FILES = $(SRCS)
endif

BFILES = $(SRCS) $(BONUS_SRCS)

OBJS =			$(FILES:.c=.o)
BONUS_OBJS =	$(BFILES:.c=.o)

CC =			gcc
RM =			rm -f
CFLAGS =		-Wall -Wextra -Werror

NAME =			libft.a


all:			$(NAME)

$(NAME):		$(OBJS)
					ar rcs $(NAME) $(OBJS)

test: 			$(NAME)

clean:
				$(RM) $(BONUS_OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)

bonus:
				@$(MAKE) BONUS_ADD=1 all


.PHONY:			all clean fclean re bonus
