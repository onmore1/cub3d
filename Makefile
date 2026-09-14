# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 22:57:10 by cpinas            #+#    #+#              #
#    Updated: 2026/06/12 12:19:26 by vananiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Ilibft -Iminiaudio

OBJ_DIR		= obj
BONUS_OBJ	= obj_bonus
LIBFT_DIR	= libft
MLX_DIR		= MLX42
MINIAUDIO_DIR	= miniaudio

LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= $(MLX_DIR)/build/libmlx42.a
MLX_INC		= -I $(MLX_DIR)/include
MLX_FLAGS	= $(MLX_LIB) -ldl -lglfw -pthread -lm
MINIAUDIO_HDR	= $(MINIAUDIO_DIR)/miniaudio.h

MANDATORY_SRCS = src/main.c src/start.c src/start_2.c \
	src/init/init.c src/init/init_2.c src/init/load_assets.c \
	src/init/settings/get_settings.c \
	src/init/settings/get_settings_utils.c \
	src/init/settings/init_settings.c \
	src/init/settings/color_parsing.c \
	src/init/settings/texture_parsing.c \
	src/init/map/get_map.c src/init/map/check_map.c \
	src/init/map/check_map_utils.c src/init/map/flood_fill.c \
	src/render/render.c src/render/render_2.c src/render/render_3.c \
	src/render/render_utils.c src/render/dda.c \
	src/movement/player_update.c src/movement/player_update_2.c \
	src/movement/player_update_3.c \
	src/movement/player_movement.c src/movement/player_movement_2.c \
	src/movement/player_rotate.c \
	src/utils/utils.c src/utils/cleanup.c src/utils/cleanup_2.c

STUB_SRCS = src/mandatory_stubs.c src/mandatory_stubs_2.c

BONUS_SRCS = src/init/enemies.c \
	src/init/map/init_doors.c \
	src/combat/hit_detection.c src/combat/hit_detection_2.c \
	src/combat/enemy_animations.c \
	src/render/render_enemies.c src/render/render_enemies_2.c \
	bonus/minimap.c bonus/minimap_2.c \
	bonus/gun_bop.c bonus/gun_bop_2.c \
	bonus/animation_guns.c bonus/animation_guns_2.c \
	bonus/animation_guns_3.c \
	bonus/animation_guns_utils.c bonus/animation_guns_utils_2.c \
	bonus/ai.c bonus/ai_2.c \
	bonus/ai_utils.c bonus/ai_utils_2.c \
	bonus/doom_guy.c bonus/doom_guy_2.c bonus/doom_guy_3.c \
	bonus/audio.c \
	bonus/doors_interact.c bonus/doors_interact_2.c \
	bonus/ui.c

MANDATORY_OBJS	= $(MANDATORY_SRCS:%.c=$(OBJ_DIR)/%.o) \
				  $(STUB_SRCS:%.c=$(OBJ_DIR)/%.o)
ALL_OBJS		= $(MANDATORY_SRCS:%.c=$(BONUS_OBJ)/%.o) \
				  $(BONUS_SRCS:%.c=$(BONUS_OBJ)/%.o)


GREEN		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
RESET		= \033[0m

all: $(LIBFT) $(MLX_LIB) $(MINIAUDIO_HDR) $(NAME)

$(NAME): $(MANDATORY_OBJS)
	@echo "$(GREEN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(MLX_INC) $(MANDATORY_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

bonus: $(LIBFT) $(MLX_LIB) $(MINIAUDIO_HDR) $(ALL_OBJS)
	@echo "$(GREEN)Linking bonus objects...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS $(MLX_INC) $(ALL_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) (bonus) created successfully!$(RESET)"

$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(BONUS_OBJ)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $< (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS $(MLX_INC) -c $< -o $@

$(BONUS_OBJ)/bonus/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $< (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS $(MLX_INC) -c $< -o $@

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "$(YELLOW)MLX42 not found, cloning...$(RESET)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@chmod +x $(MLX_DIR)/tools/*.sh 2>/dev/null || true
	@echo "$(YELLOW)Building MLX42...$(RESET)"
	@cmake -B $(MLX_DIR)/build $(MLX_DIR) --log-level=ERROR
	@cmake --build $(MLX_DIR)/build -j4
	@echo "$(GREEN)MLX42 compiled!$(RESET)"

$(MINIAUDIO_HDR):
	@mkdir -p $(MINIAUDIO_DIR)
	@if [ ! -f $(MINIAUDIO_HDR) ]; then \
		echo "$(YELLOW)miniaudio.h not found, downloading...$(RESET)"; \
		curl -sL https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h \
			-o $(MINIAUDIO_HDR); \
		echo "$(GREEN)miniaudio.h downloaded!$(RESET)"; \
	fi

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled!$(RESET)"

clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ)
	@echo "$(RED)Object files removed!$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Executable removed!$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(MLX_DIR)/build
	@echo "$(RED)MLX42 build removed!$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
