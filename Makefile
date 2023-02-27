# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 15:12:35 by mmakinen          #+#    #+#              #
#    Updated: 2023/02/24 12:44:36 by mmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

# Directory settings
SRC_DIR 	=	src
INC_DIR 	=	include
STB_DIR		=	$(INC_DIR)/vendor/stb_image
OBJ_DIR 	=	obj
LIB_DIR 	=	lib

STB_DIR 	=	$(INC_DIR)/vendor/stb_image
STB_SRC 	=	$(STB_DIR)/stb_image.cpp
GLFW		=	$(LIB_DIR)/libglfw3.a
GLEW		=	$(LIB_DIR)/libGLEW.a

CXXFLAGS 	= 	-Wall -Wextra -std=c++11
CFLAGS 		=	-Wall -Wextra
CPPFLAGS 	=	-Iinclude -MMD -MP
LDFLAGS 	=	-L$(LIB_DIR)
ifeq ($(UNAME), Linux)
	LDLIBS 		=	-lGLEW -lglfw3 -lOpenGL -ldl -lGL -lX11 -lXrandr -lXext -lXi -lXcursor -lXinerama -pthread -lfreetype
else ifeq ($(UNAME), Darwin)
	LDLIBS 		=	-lglfw3 -lOpenGL -ldl -lGL -lX11 -lXrandr -lXext -lXi -lXcursor -lXinerama -lpthread -lfreetype -framework Cocoa -framework IOKit -framework CoreVideo
endif
CXX =			g++ -g
CC =			gcc -g
NAME =			scop

INCLUDES 	=	-I $(INC_DIR)/

GLFW_B_DIR	=	dependencies/glfw-3.3.8/build

# Source files
STB_SRC		=	$(STB_DIR)/stb_image.cpp
#SRCS		:=	$(wildcard $(SRC_DIR)/*.cpp)
SRCS 		=	main.cpp error_handling.cpp index_buffer.cpp renderer.cpp shader.cpp \
				texture.cpp vertex_array.cpp vertex_buffer.cpp mesh.cpp stb_image.cpp
SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))
OBJS 		=	$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.opp, $(SRC)) $(OBJ_DIR)/stb_image.opp
STB			=	$(OBJ_DIR)/stb_image.opp

DEPS =			$(wildcard $(INC_DIR)/%.hpp)

all: $(NAME) | $(GLEW) $(GLFW)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/stb_image.opp: $(STB_SRC) $(STB_DIR)/stb_image.h | $(OBJ_DIR)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -c $< -o $@

$(OBJ_DIR)/%.opp: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -c $< -o $@

# TODO Need rules for compiling GLFW and glew from .zip and source and copy file to include and lib

$(GLFW): | $(GLFW_B_DIR) $(LIB_DIR)
	cmake -S dependencies/glfw-3.3.8 -B dependencies/glfw-3.3.8/build
	sudo make -C dependencies/glfw-3.3.8/build
	mv dependencies/glfw-3.3.8/build/src/libglfw3.a $(LIB_DIR)/

$(GLFW_B_DIR):
	mkdir -p dependencies/glfw-3.3.8/build

$(GLEW): | $(LIB_DIR)
	sudo make -C dependencies/glew-2.1.0/auto
	sudo make -C dependencies/glew-2.1.0
	mv dependencies/glew-2.1.0/lib/libGLEW.a $(LIB_DIR)/
	mv dependencies/glew-2.1.0/include/GL include/

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

libs: $(LIBS)

clean:
	rm -f $(OBJ_DIR)/*

fclean: clean
	rm -f $(NAME)

re: fclean all

tidy: all clean

.PHONY: all clean fclean re tidy
