# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 15:12:35 by mmakinen          #+#    #+#              #
#    Updated: 2023/02/24 12:16:06 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

CXXFLAGS 	:= 	-Wall -Wextra -Werror -std=c++11
CFLAGS 		:=	-Wall -Wextra -Werror
CPPFLAGS 	:=	-Iinclude -MMD -MP
LDFLAGS 	:=	-Llib
ifeq ($(UNAME), Linux)
	LDLIBS 		:=	-lGLEW -lglfw3 -lOpenGL -ldl -lGL -lX11 -lXrandr -lXext -lXi -lXcursor -lXinerama -pthread -lfreetype
else ifeq ($(UNAME), Darwin)
	LDLIBS 		:=	-lglfw3 -lOpenGL -ldl -lGL -lX11 -lXrandr -lXext -lXi -lXcursor -lXinerama -lpthread -lfreetype -framework Cocoa -framework IOKit -framework CoreVideo
endif
CXX =			g++ -g
CC =			gcc -g
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
STB_SRC		=	$(STB_DIR)/stb_image.cpp
#SRCS		:=	$(wildcard $(SRC_DIR)/*.cpp)
SRCS 		=	main.cpp error_handling.cpp index_buffer.cpp renderer.cpp shader.cpp \
				texture.cpp vertex_array.cpp vertex_buffer.cpp mesh.cpp
SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))
OBJS 		=	$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.opp, $(SRC)) $(OBJ_DIR)/stb_image.opp
STB			=	$(OBJ_DIR)/stb_image.opp

DEPS =			$(wildcard $(INC_DIR)/%.hpp)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/stb_image.opp: $(STB_SRC) $(STB_DIR)/stb_image.h | $(OBJ_DIR)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -c $< -o $@

$(OBJ_DIR)/%.opp: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -c $< -o $@

# TODO Need rules for compiling GLFW and glew from .zip and source and copy file to include and lib

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ_DIR)/*

fclean: clean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all clean fclean re tidy
