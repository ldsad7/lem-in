# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 17:36:37 by bsprigga          #+#    #+#              #
#    Updated: 2019/04/07 15:16:54 by tsimonis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re rebuild_lib re1 fclean1

NAME = lem-in

INCLUDES := ./includes \
			./libft/includes \
			/Users/$(USER)/.brew/Cellar/sdl2/2.0.9_1/include/SDL2 \
			/Users/$(USER)/.brew/Cellar/sdl2_image/2.0.4/include/SDL2 \
			/Users/$(USER)/.brew/Cellar/sdl2_gfx/1.0.4/include/SDL2 
CC = clang
FLAGS := -Wall -Werror -Wextra -g
VPATH := . srcs

SRCS =	lem_in_part_1.c \
		lem_in_part_2.c \
		read_input_part_1.c \
		read_input_part_2.c \
		read_input_part_3.c \
		read_input_part_4.c \
		support_part_1.c \
		support_part_2.c \
		support_part_3.c \
		support_part_4.c \
		support_part_5.c \
		algorithm_part_1.c \
		algorithm_part_2.c \
		algorithm_part_3.c \
		algorithm_part_4.c \
		algorithm_part_5.c \
		visualization.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft/libft.a $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) $(addprefix -I,$(INCLUDES)) -L./libft -lft \
	-L/Users/$(USER)/.brew/Cellar/sdl2/2.0.9_1/lib -lSDL2 \
	-L/Users/$(USER)/.brew/Cellar/sdl2_image/2.0.4/lib -lSDL2_image \
	-L/Users/$(USER)/.brew/Cellar/sdl2_gfx/1.0.4/lib -lSDL2_gfx -o $@

libft/libft.a:
	$(MAKE) -C libft

$(OBJECTS): %.o: %.c
	gcc $(FLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDES))

clean:
	rm -f $(OBJECTS)
	#$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)

re: fclean all

rebuild_lib:
	$(MAKE) re -C libft

re1: rebuild_lib fclean all

fclean1: fclean
	$(MAKE) fclean -C libft
