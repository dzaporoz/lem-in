# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/14 19:11:43 by dzaporoz          #+#    #+#              #
#    Updated: 2019/02/15 17:46:36 by dzaporoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS =	-Wall -Wextra -Werror -O3

SRC_DIR = ./src

HDR_DIR = ./src

LIBA = ./libft/libftprintf.a

COMPILED = main.o auxilliary.o bfs_traversal.o data_reading.o data_release.o data_validation.o find_paths.o intermediate_path_deletion.o paths_selection.o paths_sort.o prepare_paths_data.o print_data.o print_moves.o unique_path_saving.o

all: $(NAME)

$(COMPILED): %.o: $(SRC_DIR)/%.c
	gcc -c $(FLAGS) -I $(HDR_DIR) $< -o $@

$(NAME): $(COMPILED)
	@make -C libft
	gcc -o $(NAME) $(FLAGS) $(COMPILED) -I $(HDR_DIR) $(LIBA)

clean:
	@rm -f $(COMPILED)
	make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libftprintf.a

re: fclean all
