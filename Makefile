# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 15:12:35 by mmakinen          #+#    #+#              #
#    Updated: 2023/01/31 15:12:37 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SHELL =			/bin/sh
.SUFFIXES =		
.SUFFIXES =		.cpp .opp .hpp
CC =			clang
FLAGS = 		-Wall -Wextra -Werror -O3
NAME =			scop
SRC_DIR =		src
INC_DIR =		include
OBJ_DIR =		obj
SRCS =			main.opp 
SFML = ./SFML-2.5.1

LIB =			libft/libft.a
MAC_LIBS =		-lmlx -lm -framework OpenGL -framework AppKit
LINUX_LIBS =	-lX11 -lXext -lmlx -lm -lpthread
INCLUDES =		-I $(INC_DIR)/ -I ./SFML-2.5.1/include/SFML/
OBJECTS =		$(addprefix $(OBJ_DIR)/, $(SRCS))


all:
	make -C dependencies/glew-2.1.0/auto
	make -C dependencies/glew-2.1.0
	cmake -S dependencies/SFML-2.5.1 -B dependencies/SFML-2.5.1/build
	make -C dependencies/SFML-2.5.1/build/
	cmake -S . -B build
	make -C build/
#all: $(NAME)

$(OBJ_DIR)/%.opp: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDES)

$(NAME): $(OBJECTS) $(LIB)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ $^ $(MAC_LIBS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIB):
	@make -C libft/

linux: $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) $^ $(LINUX_LIBS)

libclean:
	@make -C libft/ clean

libfclean:
	rm -f $(LIB)

clean: libclean
	rm -f $(OBJECTS) 
	rm -rf $(OBJ_DIR)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

re_linux: fclean linux

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy linux re_linux
