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

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
#FLAGS = 		-Wall -Wextra -Werror -fopenmp -std=c++11 #seems to be enough on debian
FLAGS = 		-Wall -Wextra -Werror -fopenmp -std=c++11 -Wno-return-type -fPIE
endif
ifeq ($(UNAME), Darwin)
FLAGS = 		-Wall -Wextra -Werror -fopenmp -std=c++11
endif
SHELL =			/bin/sh
.SUFFIXES =		
.SUFFIXES =		.cpp .opp .hpp
CC =			g++ -g
NAME =			scop
SRC_DIR =		src
INC_DIR =		include
OBJ_DIR =		obj
SRCS =			main.opp error_handling.opp  index_buffer.opp renderer.opp shader.opp texture.opp vertex_array.opp vertex_buffer.opp

GLEW_DIR =		./dependencies/glew-2.1.0
GLEW_INC =		${GLEW_DIR}/GL/include
GLEW_LIB =		${GLEW_DIR}/lib

SFML_DIR =		./dependencies/SFML-2.5.1
SFML_INC =		${SFML_DIR}/SFML/include
SFML_BUILD =	${SFML_DIR}/build
SFML_LIB =		${SFML_BUILD}/lib

STB_DIR =		${INC_DIR}/vendor/stb_image
STB_SRC =		${STB_DIR}/stb_image.cpp
LIBGLEW =		${GLEW_LIB}/libGLEW.a
LIBSFML =		${SFML_LIB}/libsfml-window-s-d.a ${SFML_LIB}/libsfml-system-s-d.a

MAC_LIBS =		-framework OpenGL -framework AppKit
LINUX_LIBS =	-lX11 -lXext -lmlx -lm -lpthread -lGL -lXrandr -ludev -lpthread -lfreetype
INCLUDES =		-I $(INC_DIR)/ -I ${SFML_INC}/ -I ${GLEW_INC} -I ${STB_DIR}
OBJECTS =		$(addprefix $(OBJ_DIR)/, $(SRCS))

all: $(NAME)

$(OBJ_DIR)/%.opp: $(SRC_DIR)/%.cpp $(LIB) ${LIBGLEW} ${LIBSFML} | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(FLAGS) -o $@ $< $(INCLUDES)

$(NAME): $(OBJECTS) ${STB_SRC} $(LIB) ${LIBGLEW} ${LIBSFML}
	$(CC) $(FLAGS) $(INCLUDES) -o $@ $^ $(LINUX_LIBS) 

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBGLEW):
	make -C dependencies/glew-2.1.0/auto
	make -C dependencies/glew-2.1.0

$(LIBSFML):
	cmake -S dependencies/SFML-2.5.1 -B dependencies/SFML-2.5.1/build
	make -C dependencies/SFML-2.5.1/build/

linux: $(OBJECTS) $(LIB)
	@$(CC) $(FLAGS) $(INCLUDES) -o $(NAME) $^ $(LINUX_LIBS)

clean: 
	rm -f $(OBJECTS) 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

re_linux: fclean linux

tidy: all clean

.PHONY: all libclean libfclean clean fclean re tidy linux re_linux
