# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:48:38 by ailopez-          #+#    #+#              #
#    Updated: 2023/01/03 01:55:07 by aitoraudica      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

NAME		:= fdf

SRC_DIR		:= src/
OBJ_DIR		:= obj/
CC			:= gcc
CFLAGS		:= -g -O3 -Wall -Werror -Wextra
#FSANITIZE	:= -fsanitize=address -g3
FSANITIZE	:= 
NOFLAGS		:= -g
RM			:= rm -f

INC		 		:= inc/
LIB				:= lib/
PRINTF_DIR		:= $(LIB)ft_printf/
PRINTF			:= $(PRINTF_DIR)libftprintf.a
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
				map_load map_draw get_next_line menu map_utils map_utils2 draw_utils \
				draw_utils2 geometry2 utils2

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))
INCS		= 	$(addprefix $(INCLUDE), $(addsuffix .h, $(INC_FILES)))
###

OBJF		=	.cache_exists

all:	makelibs
		@$(MAKE) $(NAME)

makelibs:	
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(MINILIBX_DIR)

-include 	${DEPS}
$(NAME):	$(OBJ)		
			@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) $(MINILIBXCC) $(OPENGL) -o $(NAME)		
			@echo "👉 $(BLUE)$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) $(PRINTF) $(MINILIBXCC) $(OPENGL) -o $(NAME)$(DEF_COLOR)"
			@echo "$(GREEN)✨ FDF compiled!$(DEF_COLOR)"

bonus:		
			@$(MAKE) all
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) | $(OBJF)
			@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
			$(CC) $(CFLAGS) -MMD -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)
	@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"	

$(MINILIBX):
	@make -C $(MINILIBX_DIR)
	@echo "$(GREEN)Minilibx compiled!$(DEF_COLOR)"			

clean:
			@make clean -sC $(PRINTF_DIR)
			@echo "$(CYAN)ft_printf object and dependency files cleaned.$(DEF_COLOR)"
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

