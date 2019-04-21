# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lwyl-the <lwyl-the@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 10:25:27 by rgyles            #+#    #+#              #
#    Updated: 2019/04/21 18:29:22 by lwyl-the         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

SRC_DIR = sources

PRS_SRC_DIR = $(SRC_DIR)/parser_sources

UI_SRC_DIR = $(SRC_DIR)/ui_sources

TEXTURE_SRC_DIR = $(SRC_DIR)/texture_sources

GEOMETRY_SRC_DIR = $(SRC_DIR)/geometry

EFFECTS_SRC_DIR = $(SRC_DIR)/effects

FIGURE_SRC_DIR = $(SRC_DIR)/figure

OBJ_DIR = objects

LIBFT_DIR = libft

KISS_DIR = kiss_sdl

KISS_SDL = $(KISS_DIR)/kisssdl.a

LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -O2 -g -Wall -Wextra #-Werror

SDL =  -F ./includes/frameworks/ -framework SDL2 \
								-framework SDL2_image \
								-framework SDL2_ttf \
								-framework SDL2_mixer

INCLUDES = -I includes -I libft -I kiss_sdl -I includes/frameworks/SDL2.framework/Headers \
			-I includes/frameworks/SDL2_image.framework/Versions/A/Headers \
			-I includes/frameworks/SDL2_ttf.framework/Versions/A/Headers \
			-I includes/frameworks/SDL2_mixer.framework/Versions/A/Headers

SRC = main.c\
	  progress_bar.c\
	  read_config_file.c\
	  event_handler.c\
	  init_config.c\
	  parse_helper.c\
	  get_vector.c\
	  init_shapes.c\
	  identify_shape.c\
	  init_groups.c\
	  shape_parse_main.c\
	  init_dimensions.c\
	  shape_parse_opt.c\
	  init_function.c\
	  init_texture.c\
	  effect_check.c\
	  init_texture_dimensions.c\
	  init_lighting.c\
	  init_physics.c\
	  create_img.c\
	  trace_ray.c\
	  primitives_simple.c\
	  primitives_diff.c\
	  primitives_inf.c\
	  get_color.c\
	  texture.c\
	  normal.c\
	  light.c\
	  shadow.c\
	  reflection.c\
	  refraction.c\
	  transperency.c\
	  matrix.c\
	  fractal.c\
	  matrix_euler.c\
	  vec3_1.c\
	  vec3_2.c\
	  vec2.c\
	  constructive_geometry.c\
	  free_args.c\
	  disrubtion_effects.c\
	  color_disrubtion.c\
	  convert_color.c\
	  shape_summ.c\
	  noise.c\
	  sphere_texture.c\
	  plane_texture.c\
	  cylinder_texture.c\
	  cone_texture.c\
	  torus_texture.c\
	  box_texture.c\
	  pthread.c\
	  ui_main.c\
	  ui_error.c\
	  ui_dirread.c\
	  ui_init.c\
	  ui_light.c\
	  ui_buttons.c\
	  ui_ambient.c\
	  ui_saving.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
SRC_LIN = $(addprefix $(SRC_DIR)/, $(SRC))

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

all: $(NAME)

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
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

$(OBJ_DIR)/%.o: $(PRS_SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

$(OBJ_DIR)/%.o: $(UI_SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

$(OBJ_DIR)/%.o: $(TEXTURE_SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

$(OBJ_DIR)/%.o: $(GEOMETRY_SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

$(OBJ_DIR)/%.o: $(EFFECTS_SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

$(OBJ_DIR)/%.o: $(FIGURE_SRC_DIR)/%.c includes/rt.h includes/shape.h includes/constants.h includes/vector.h includes/ui.h| $(OBJ_DIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< -F includes/frameworks/

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
