# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 10:25:27 by rgyles            #+#    #+#              #
#    Updated: 2019/03/31 16:22:30 by lwyl-the         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRC_DIR = sources

OBJ_DIR = objects

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -o2 -g -Wall -Wextra #-Werror

INCLUDES = -I SDL2.framework/Headers -I includes -I libft

SRC = main.c\
	  event_handler.c\
	  init_config.c\
	  init_shapes.c\
	  init_physics.c\
	  init_texture.c\
	  parse_one.c\
	  parse_two.c\
	  parse_three.c\
	  init_lighting.c\
	  create_img.c\
	  matrix.c\
	  vector.c\
	  free_args.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(BLUE)Compiling RT...$(NC)"
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) -F . -framework SDL2
	@echo "$(GREEN)RT is ready!$(NC)"

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@echo "$(GREEN)Objects directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/rt.h | $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Deleting libraries and binary...$(NC)"
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

test: all
	@echo "$(GREEN)Testing...$(NC)"
	@./RT parser/test1.json

scene: all
	@echo "$(GREEN)Testing...$(NC)"
	@./RT parser/scene.json

.PHONY: all clean fclean re test
