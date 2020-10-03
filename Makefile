# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljanette <ljanette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/01 17:51:30 by ljanette          #+#    #+#              #
#    Updated: 2020/10/03 11:36:33 by ljanette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARS
NAME	= Cub3d
CC		= gcc

INC_DIR = includes
SRC_DIR = srcs
OBJ_DIR = obj

#SRC_FILES	= *.c map/*.c
INC_FILES	= includes/cub3d/cub3d.h includes/cub3d/get_next_line.h includes/cub3d/libft.h includes/cub3d/mlx.h
SRC_FILES	= \
			main.c 					cub3d_utils.c 	engine/player.c	engine/raycast.c engine/draw.c engine/raycast-2.c\
			map_parser/map_parser.c		map_parser/settings_parser.c\
			map_parser/get_next_line.c	map_parser/get_next_line_utils.c\
			map_parser/map_checker.c map_parser/settings_checker.c

INC = mlx_linux cub3d libft
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT = includes/libft/libft.a

# COLORS
RED		= \033[1;31m
BOLD	= \033[1m
NC		= \033[0m

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C includes/libft bonus
	@$(MAKE) -C includes/libft clean

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	@$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ) $(addprefix -L$(INC_DIR)/, $(INC)) includes/libft/libft.a
	@echo "\n$(BOLD)MAKE:$(NC)\t'$(NAME)' created"

$(OBJ_DIR):
	@mkdir -p obj
	@mkdir -p obj/map_parser
	@mkdir -p obj/engine

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) -Imlx $(addprefix -I$(INC_DIR)/, $(INC)) -c $< -o $@
	@echo "$(BOLD)MAKE:$(NC)\t'$@' created"

clean:
	@rm -rf obj
	@echo "$(BOLD)MAKE:$(NC)\tdirectory 'obj' removed"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BOLD)MAKE:$(NC)\t'$(NAME)' removed"

re:
	$(MAKE) fclean
	$(MAKE) all

libft_fclean:
	$(MAKE) -C includes/libft fclean
