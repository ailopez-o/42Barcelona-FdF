# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:48:38 by ailopez-          #+#    #+#              #
#    Updated: 2022/06/03 13:50:22 by aitoraudi        ###   ########.fr        #
#    Updated: 2022/05/24 00:35:24 by aitorlope        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#Variables

NAME		= a.out
INCLUDE		= inc/
LIB			= lib
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra -MMD 
NOFLAGS		= -g
RM			= rm -f
MLX		= 	miniliblx/minilibx_macos

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRC_FILES	=	main keycontrol mouse utils matrix geometry map get_next_line
INC_FILES	= 	fdf keycodes

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS		= 	$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))
###

OBJF		=	.cache_exists

all:	makelibs
	@$(MAKE)	$(NAME)

makelibs:	
			@$(MAKE) -C $(LIB)/$(MLX)
			@$(MAKE) -C $(LIB)/libft
			
-include 	${DEPS}
$(NAME):	$(OBJ) $(INCS)
			@$(CC)  ${CFLAGS} $(OBJ) $(LIB)/libft/libft.a -I minilibx -L $(LIB)/$(MLX) -lmlx -framework OpenGL -framework AppKit -o $@			
			@echo "$(MAGENTA)$(CC) ${CFLAGS} $(OBJ) $(LIB)/libft/libft.a -I minilibx -L $(LIB)/$(MLX) -lmlx -framework OpenGL -framework AppKit -o $@	$(DEF_COLOR)"
			@echo "$(GREEN)FDF compiled!$(DEF_COLOR)"

bonus:		
			@$(MAKE) all
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIB)/$(MLX)
			@echo "$(CYAN)Fdf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			$(RM) -f $(NAME)
			@echo "$(CYAN)Fdf executable files cleaned!$(DEF_COLOR)"
			$(RM) -f $(LIB)/$(MLX)/libmlx.a
			$(RM) -f $(LIB)/libft/libft.a
			@echo "$(CYAN)libmlx.a lib cleaned!$(DEF_COLOR)"

re:			fclean 
			@$(MAKE)	
			@echo "$(GREEN)Cleaned and rebuilt everything for Fdf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm

