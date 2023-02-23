# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 15:12:35 by mmakinen          #+#    #+#              #
#    Updated: 2023/02/23 17:21:56 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

CXXFLAGS 	:= 	-Wall -Wextra -Werror -std=c++11
CFLAGS 		:=	-Wall -Wextra -Werror
CPPFLAGS 	:=	-Iinclude -MMD -MP
LDFLAGS 	:=	-Llib
LDLIBS 		:=	-lglfw3 -lOpenGL -ldl -lGL -lX11 -lXrandr -lXext -lXi -lXcursor -lXinerama -lpthread -lfreetype

CXX =			g++ -g
CC =			gcc
NAME =			scop

# Directory settings
SRC_DIR 	=	src
INC_DIR 	=	include
STB_DIR		=	$(INC_DIR)/vendor/stb_image
OBJ_DIR 	=	obj
LIB_DIR 	=	lib

STB_DIR 	=	$(INC_DIR)/vendor/stb_image
STB_SRC 	=	$(STB_DIR)/stb_image.cpp

INCLUDES 	=	-I $(INC_DIR)/

# Source files
GLAD_SRC	:=	$(SRC_DIR)/glad.c
STB_SRC		:=	$(STB_DIR)/stb_image.cpp
SRCS		:=	$(wildcard $(SRC_DIR)/*.cpp)
#SRCS 		:=	main.cpp error_handling.cpp index_buffer.cpp renderer.cpp shader.cpp \
				texture.cpp vertex_array.cpp vertex_buffer.cpp mesh.cpp vector.cpp
OBJS 		:=	$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.opp, $(SRCS)) $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(GLAD_SRC)) stb_image.opp
STB			:=	$(OBJ_DIR)/stb_image.opp

GLAD_DEP =		$(INC_DIR)/glad/glad.h
DEPS =			$(wildcard $(INC_DIR)/%.hpp) $(GLAD_DEP)

all: $(NAME)

$(NAME): $(OBJS) $(STB)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(STB):
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -c -o $(OBJ_DIR)/stb_image.opp $(STB_SRC)

$(OBJ_DIR)/%.opp: $(SRC_DIR)/%.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(GLAD_DEP) | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)



clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all clean fclean re tidy
