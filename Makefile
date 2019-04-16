# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 10:25:27 by rgyles            #+#    #+#              #
#    Updated: 2019/04/16 17:05:07 by lwyl-the         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRC_DIR = sources

OBJ_DIR = objects

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -O2 -g -Wall -Wextra #-Werror

INCLUDES = -I SDL2.framework/Headers -I includes -I libft

SRC = main.c\
	  event_handler.c\
	  init_config.c\
	  init_shapes.c\
	  parse_one.c\
	  parse_two.c\
	  init_dimensions.c\
	  init_physics.c\
	  init_texture.c\
	  init_lighting.c\
	  create_img.c\
	  primitives_simple.c\
	  primitives_diff.c\
	  primitives_inf.c\
	  get_color.c\
	  texture.c\
	  normal.c\
	  light.c\
	  shadow.c\
	  reflection.c\
	  matrix.c\
	  fractal.c\
	  matrix_euler.c\
	  vec3.c\
	  vec2.c\
	  constructive_geometry.c\
	  free_args.c\
	  init_id.c\
	  shape_summ.c\
	  init_shape_child.c\
	  disrubtion_effects.c\
	  generateNoise.c\
	  smooth_noise.c\
	  turbulence.c\
	  noise.c\
	  wood.c\
	  chess_board.c\
	  marble.c

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h| $(OBJ_DIR)
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
	@./RT scene/test1.json

scene: all
	@echo "$(GREEN)Testing...$(NC)"
	@./RT scene/scene.json

march: all
	@echo "$(GREEN)Testing...$(NC)"
	@./RT scene/march.json

kk: all
	@echo "$(GREEN)Testing...$(NC)"
	@./RT scene/kk.json

allf: all
	@echo "$(GREEN)Testing...$(NC)"
	@./RT scene/all_figures.json

.PHONY: all clean fclean re test
