# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/18 16:39:22 by rcammaro          #+#    #+#              #
#    Updated: 2021/07/25 18:42:26 by rcammaro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_DIR = get_next_line
GNL_FILES = get_next_line.c get_next_line_utils.c
GNL_SRCS = $(addprefix $(GNL_DIR)/,$(GNL_FILES))
GNL_OBJS = $(GNL_SRCS:.c=.o)

ADD_ONS_DIR = add_ons
ADD_ONS_FILES =	ft_atof.c ft_atof_mv_ptr.c ft_atoi_mv_ptr.c \
				ft_free_split.c ft_isspace.c ft_split_charset.c ft_strcmp.c
ADD_ONS_SRCS = $(addprefix $(ADD_ONS_DIR)/,$(ADD_ONS_FILES))
ADD_ONS_OBJS = $(ADD_ONS_SRCS:.c=.o)

FT_CORE_DIR = libft_core

HEADERS =	$(addprefix $(GNL_DIR)/,get_next_line.h) \
			$(addprefix $(ADD_ONS_DIR)/,add_ons.h)

INCLUDES = -I./$(GNL_DIR) -I./$(ADD_ONS_DIR) -I./$(FT_CORE_DIR)
CFLAGS		= 	-Wall -Wextra -Werror

NAME = libft.a
FT_CORE = libft_core/libft.a

all:			$(NAME)

$(NAME):		$(FT_CORE) $(GNL_OBJS) $(ADD_ONS_OBJS)
				cp $(FT_CORE) $@
				ar -rcs $@ $(GNL_OBJS) $(ADD_ONS_OBJS)

$(FT_CORE):		
				$(MAKE) bonus -C libft_core

%.o:			%.c $(HEADERS)
				$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
				$(MAKE) fclean -C libft_core
				rm -f $(GNL_OBJS) $(ADD_ONS_OBJS)

fclean:			clean
				rm -f $(NAME)
				
re:				fclean all

.PHONY:			all clean fclean re
