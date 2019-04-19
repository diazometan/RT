
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

KISS_DIR = kiss_sdl

KISS_SDL = $(KISS_DIR)/kisssdl.a

SDL =  -F includes/frameworks/ -framework SDL2 \
-framework SDL2_image \
-framework SDL2_ttf \
-framework SDL2_mixer

FLAGS = # -O2 -g -Wall -Wextra -Werror

INCLUDES = -I includes -I libft -I kiss_sdl -I includes/frameworks/SDL2.framework/Versions/A/Headers \
-I includes/frameworks/SDL2_image.framework/Versions/A/Headers \
-I includes/frameworks/SDL2_ttf.framework/Versions/A/Headers \
-I includes/frameworks/SDL2_mixer.framework/Versions/A/Headers 

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
	  constructive_shapes.c\
	  matrix_euler.c\
	  vec3.c\
	  vec2.c\
	  constructive_geometry.c\
	  free_args.c\
	  init_id.c\
	  shape_summ.c\
	  init_shape_child.c\
	  generateNoise.c\
	  smooth_noise.c\
	  turbulence.c\
	  noise.c\
	  wood.c\
	  chess_board.c\
	  marble.c\
	  ui_main.c\
	  ui_error.c\
	  ui_dirread.c\
	  ui_init.c\
	  ui_light.c\
	  ui_buttons.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC_LIN = $(addprefix $(SRC_DIR)/, $(SRC))

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

all: $(NAME)

FLAGS_LINUX =  -I ./includes/ ./kiss_sdl/libkisssdl.a -I ./includes/frameworks/SDL2_ttf.framework/Versions/A/Headers \
 	-I ./includes/frameworks/SDL2_image.framework/Versions/A/Headers \
	 -I ./kiss_sdl -I ./libft -lm -lpthread -lSDL2main -lSDL2  -lSDL2_ttf -lSDL2_image

#linux: #$(LIBFT) $(KISS_SDL) #$(OBJ)
#	sudo gcc $(FLAGS) $(OBJ) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

linux:
	sudo gcc $(FLAGS) $(SRC_LIN) $(LIBFT) $(FLAGS_LINUX) -o $(NAME)

$(NAME): $(LIBFT) $(KISS_SDL) $(OBJ)
	@echo "$(BLUE)Compiling RT...$(NC)"
	@gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(KISS_SDL) $(SDL)
	@echo "$(GREEN)RT is ready!$(NC)"

$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(NC)"
	@make -C $(LIBFT_DIR)

$(KISS_SDL):
	@echo "$(BLUE)Compiling kiss_sdl...$(NC)"
	@make -C $(KISS_DIR)

$(OBJ_DIR):
	@echo "$(GREEN)Objects directory is created!$(NC)"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<  -F includes/frameworks/

clean:
	@echo "$(RED)Deleting object files...$(NC)"
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Deleting libraries and binary...$(NC)"
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(KISS_DIR) fclean

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