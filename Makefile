# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 17:47:56 by rlabbiz           #+#    #+#              #
#    Updated: 2023/08/19 17:03:10 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLG = -Wall -Wextra -Werror
MLX = -Imlx -lmlx -framework OpenGL -framework AppKit
NAME = cub3d
OBJ =	check_map.o \
		draw_map.o \
		handle_key.o
MAIN = cub3d.c
DEF = cub3d.h
LIBFT = libft/libft.a

GRN=\033[0;32m
RED=\033[0;31m
BLU=\033[0;34m
END=\033[0m

%.o: %.c $(DEF)
	@$(CC) -c -o $@ $< $(FLG)
	@echo "$(GRN)$<... DONE!$(END)"

.PHONY : all clean fclean re 

all : $(NAME)

$(LIBFT) :
	@make bonus -C libft
	@echo "$(GRN)libft... DONE!$(END)"

$(NAME) : $(OBJ) $(DEF) $(MAIN) $(LIBFT)
	@$(CC) $(FLG) $(MLX) $(MAIN) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GRN)create the cub3d... DONE!$(END)"

clean : 
	@rm -rf $(OBJ)
	@make clean -C libft
	@echo "$(GRN)Remove all objects file... DONE!$(END)"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo "$(GRN)Remove the cub3d... DONE!$(END)"

re : fclean all 
