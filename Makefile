# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 15:12:35 by mmakinen          #+#    #+#              #
#    Updated: 2023/02/23 16:32:33 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

CXXFLAGS 	:= 	-Wall -Wextra -Werror -std=c++11
CFLAGS 		:=	-Wall -Wextra -Werror
CPPFLAGS 	:=	-Iinclude -MMD -MP
LDFLAGS 	:=	-Llib
LDLIBS 		:=	-lX11 -lXext -lXi -ldl -lXcursor -lXinerama -lpthread -lGL -lXrandr

CXX =			g++ -g
CC =			GCC
NAME =			scop

# Directory settings
SRC_DIR =		src
INC_DIR =		include
OBJ_DIR =		obj
LIB_DIR =		lib

STB_DIR =		$(INC_DIR)/vendor/stb_image
STB_SRC =		$(STB_DIR)/stb_image.cpp

INCLUDES =		-I $(INC_DIR)/

# Source files
SRCS :=			main.cpp glad.c error_handling.cpp index_buffer.cpp renderer.cpp shader.cpp \
				texture.cpp vertex_array.cpp vertex_buffer.cpp mesh.cpp vector.cpp
OBJS :=			$(patsubst $(OBJ_DIR)/%.opp,$(SRC_DIR)/%.cpp,$(SRCS))

DEPS =			$(wildcard $(INC_DIR)/%.hpp)
GLAD_DEP =		$(INC_DIR)/glad/glad.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.opp: $(SRC_DIR)/%.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(GLAD_DEP) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean: $(OBJS)
	rm -f $(OBJS)

fclean: clean $(NAME)
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all clean fclean re tidy
