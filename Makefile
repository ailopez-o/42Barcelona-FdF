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

NAME		:= fdf

SRC_DIR		:= src/
OBJ_DIR		:= obj/
CC			:= gcc
CFLAGS		:= -g -Wall -Werror -Wextra
FSANITIZE	:= -fsanitize=address -g3
NOFLAGS		:= -g
RM			:= rm -f

INC		 		:= inc/
LIB				:= lib/
LIBFT_DIR		:= $(LIB)libft/
LIBFT			:= $(LIBFT_DIR)libft.a
MINILIBX_DIR	:= $(LIB)miniliblx/minilibx_macos/
MINILIBX		:= $(MINILIBX_DIR)libmlx.a
MINILIBXCC		:= -I mlx -L $(MINILIBX_DIR) -lmlx
HEADER 			:= -I$(INC) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
OPENGL			:= -framework OpenGL -framework AppKit

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

SRC_FILES	=	main control_keys control_mouse control_utils utils matrix geometry \
				map_load map_draw get_next_line menu map_utils draw_utils

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS		= 	$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))
###

OBJF		=	.cache_exists

all:	$(NAME)
			
-include 	${DEPS}
$(NAME):	$(LIBFT) $(MINILIBX) $(OBJ)
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(LIBFT) $(MINILIBXCC) $(OPENGL) -o $(NAME)		
			@echo "$(BLUE)$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(LIBFT) $(MINILIBXCC) $(OPENGL) -o $(NAME)$(DEF_COLOR)"
			@echo "$(GREEN)FDF compiled!$(DEF_COLOR)"

			

bonus:		
			@$(MAKE) all
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) -MMD -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -sC $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"	

$(MINILIBX):
	@make -sC $(MINILIBX_DIR)
	@echo "$(GREEN)Minilibx compiled!$(DEF_COLOR)"			

clean:
			@make clean -sC $(LIBFT_DIR)
			@echo "$(CYAN)Libft object and dependency files cleaned.$(DEF_COLOR)"
			@make clean -C $(MINILIBX_DIR)
			@echo "$(CYAN)Minilibx object files cleaned.$(DEF_COLOR)"	
			$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)Fdf object files cleaned!$(DEF_COLOR)"

fclean:		clean
			$(RM) -f $(NAME)
			@echo "$(CYAN)Fdf executable files cleaned!$(DEF_COLOR)"
			$(RM) -f $(MINILIBX_DIR)libmlx.a
			@echo "$(CYAN)libmlx.a lib cleaned!$(DEF_COLOR)"			
			$(RM) -f $(LIBFT_DIR)libft.a
			@echo "$(CYAN)libft.a lib cleaned!$(DEF_COLOR)"


re:			fclean 
			@$(MAKE)	
			@echo "$(GREEN)Cleaned and rebuilt everything for Fdf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm

