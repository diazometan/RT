# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 10:25:27 by rgyles            #+#    #+#              #
#    Updated: 2019/03/07 18:57:35 by rgyles           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC_DIR = sources

OBJ_DIR = objects

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx_macos

MLX = $(MLX_DIR)/libmlx.a

FLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes -F .

SRC = main.c\
	  matrix.c\
	  key_press.c\
	  get_shapes.c\
	  check_shape.c\
	  get_light_sources.c\
	  init_camera.c\
	  create_img.c\
	  check_intersection.c\
	  plane.c\
	  sphere.c\
	  cylinder.c\
	  cone.c\
	  check_shadow.c\
	  light.c\
	  get_color.c\
	  vector.c\
	  free_args.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@echo "$(BLUE)Compiling RTv1...$(NC)"
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(MLX) $(LIBFT) -framework OpenGL -framework Appkit
	@echo "$(GREEN)RTv1 is ready!$(NC)"

$(MLX):
	@echo "$(BLUE)Compiling mlx library...$(NC)"
	@make -C $(MLX_DIR)

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@echo "$(GREEN)Objects directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/rtv1.h | $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@/bin/rm -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Deleting libraries and binary...$(NC)"
	@/bin/rm -f $(NAME)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
