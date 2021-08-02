# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/31 17:10:47 by jongpark          #+#    #+#              #
#    Updated: 2021/01/06 20:15:15 by jongpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	miniRT
SRC		=	main.c \
			my_rt.c \
			vec3.c \
			vec3_2.c \
			ray.c \
			color.c \
			util.c \
			read_file.c \
			ft_calloc.c \
			ft_split.c \
			ft_putstr_fd.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_strlcpy.c \
			ft_strncmp.c
OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CF		=	-Wall -Wextra -Werror -Imlx -Iincludes -g
LK		=	-Lmlx -lmlx -framework OpenGL -framework Appkit -Iincludes -g

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(LK) -o $(NAME) $^

%.o		:	%.c
			$(CC) $(CF) -c $< -o $@

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

f		:	all
			./$(NAME)

t		:	all
			./$(NAME) s1.rt

dbg		:	all
			lldb $(NAME) s1.rt

