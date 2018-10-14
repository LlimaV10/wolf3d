# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/16 16:42:45 by dbolilyi          #+#    #+#              #
#    Updated: 2018/08/03 15:15:55 by dbolilyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC = \
	SRC/add_elements_to_draw.c \
	SRC/add_enemies_to_draw.c \
	SRC/damage_enemy.c \
	SRC/draw.c \
	SRC/draw_elements.c \
	SRC/draw_gun_bar.c \
	SRC/draw_wall_floor_ceil.c \
	SRC/get_defaults.c \
	SRC/get_ray.c \
	SRC/get_textures.c \
	SRC/hooks.c \
	SRC/loop.c \
	SRC/loop2.c \
	SRC/loop_enemies.c \
	SRC/loop_enemies2.c \
	SRC/main.c \
	SRC/player_actions.c \
	SRC/validation.c \
	SRC/validation2.c

OBJ = $(SRC:.c=.o)

ERRFL = -Wall -Wextra -Werror

FL = -lmlx -framework OpenGL -framework AppKit -o3

PRINT = yes

all: $(NAME)

$(OBJ): %.o: %.c
	@echo "\033[93mCompiling \033[0m$@"
	@cc $(ERRFL) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "\033[93mCompiling libft\033[0m"
	@make -C ./libft
	@echo "\033[93mCompiling $(NAME)\033[0m"
	@gcc $(ERRFL) $(FL) -o $@ $(OBJ) -L libft/ ./libft/libft.a
	@echo "\033[92mDONE\033[0m"
	

clean:
	@echo "\033[91mDeleting libft objects\033[0m"
	@make -C libft/ clean
	@echo "\033[91mDeleting $(NAME) objects\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[91mDeleting libft.a\033[0m"
	@make -C libft/ fclean
	@echo "\033[91mDeleting $(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean \
	all

.PHONY: all clean fclean re libft1

.NOTPARALLEL: all clean fclean re libft1
