# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/31 17:10:47 by jongpark          #+#    #+#              #
#    Updated: 2022/02/11 15:16:02 by jongpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	miniRT
SRC		=	main.c			\
			my_rt.c			\
			vec3.c			\
			vec3_2.c		\
			ray.c			\
			color.c			\
			util.c			\
			read_file.c		\
			ft_calloc.c		\
			ft_split.c		\
			ft_putstr_fd.c	\
			ft_atoi.c		\
			ft_bzero.c		\
			ft_strlcpy.c	\
			ft_strncmp.c

SRC_DIR	=	./src/
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CF		=	-Wall -Wextra -Werror -Imlx -Iincludes -g
LK		=	-Lmlx -lmlx -framework OpenGL -framework Appkit -Iincludes -g

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(LK) -o $(NAME) $^

%.o		:	%.c
			$(CC) $(CF) -c $< -o $@

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

