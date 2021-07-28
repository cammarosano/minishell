# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 19:12:10 by rcammaro          #+#    #+#              #
#    Updated: 2021/07/28 15:28:22 by rcammaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	builtin_cd.c \
		builtin_exit.c \
		builtin_export.c \
		builtins_env_echo_pwd_unset.c \
		clear_memory.c \
		env_setup.c \
		env_utils.c \
		error.c \
		execute_binary.c \
		execute_line.c \
		expansion_2.c \
		expansion.c \
		here_doc.c \
		here_doc_2.c \
		main.c \
		parse_redirections_2.c \
		parse_redirections.c \
		parser_split_by_pipe.c \
		pipeline.c \
		preprocessor.c \
		redirections.c \
		resolve_path.c \
		run_builtin.c \
		set_var.c \
		signal_handler.c

SRC = $(addprefix src/,$(SRCS))
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
INCLUDES = -I include -I libft
LIBS = -lft -L libft -lreadline

# for 19's Macs, uncomment lines below:

# INCLUDES += -I /Users/$(USER)/.brew/opt/readline/include
# LIBS += -L /Users/$(USER)/.brew/opt/readline/lib

HEADER = include/header.h
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = minishell

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)	
			$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $@

$(LIBFT):	
			$(MAKE) all clean -C libft/

%.o:		%.c $(HEADER)
			$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME) $(LIBFT)

re:			fclean all 

.PHONY:		all clean fclean re
