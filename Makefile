# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:48:38 by ailopez-          #+#    #+#              #
#    Updated: 2022/05/18 16:15:48 by ailopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	a.out

SRCS	=	src/main.c src/events.c src/my_draws.c src/utils.c

MLX		= 	miniliblx/minilibx_macos

OBJ		=	$(SRCS:%.c=%.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NOFLAGS = 	-g

RM		=	rm -f

%.o: %.c
	$(CC) ${NOFLAGS} -Imlx -c $< -o $@

all:	makelibs
	@$(MAKE)	$(NAME)

makelibs:	
	@$(MAKE) -C $(MLX)

$(NAME): $(OBJ)
#	$(CC) $(OBJ) ${MLX}/libmlx.a -framework OpenGL -framework AppKit -o $(NAME)
	$(CC)  ${NOFLAGS} $(OBJ) -I minilibx -L $(MLX) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

#Regla para borrar todos los objetos y directorios
clean:
		${RM} ${OBJS}

#Regla para borrar todo lo que ha sido creado or el makefile
fclean:	clean
		${RM} ${NAME} 

#Regla  para rehacer todo
re:		fclean all

.PHONY: fclean, all, clean, re

