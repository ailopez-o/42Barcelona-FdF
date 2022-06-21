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

SRCS		=	main.c

OBJ		=	$(SRCS:%.c=%.o)

CC		=	gcc

#CFLAGS	=	-Wall -Wextra -Werror

CFLAGS = 

RM		=	rm -f

%.o: %.c
	$(CC) ${CFLAGS} -Imlx -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)


#Regla para borrar todos los objetos y directorios
clean:
		${RM} ${OBJS}

#Regla para borrar todo lo que ha sido creado or el makefile
fclean:	clean
		${RM} ${NAME} 

#Regla  para rehacer todo
re:		fclean all

.PHONY: fclean, all, clean, re

