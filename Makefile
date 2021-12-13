# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabir <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 16:54:50 by hsabir            #+#    #+#              #
#    Updated: 2021/12/13 12:23:11 by hsabir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAMES
NAME = fdf

LFT_NAME = libft.a

LMLX_NAME_MMS = libmlx.dylib
LMLX_NAME_MACOS_SIERRA = libmlx.a
LMLX_NAME_LINUX = libmlx.a

# MAKE
MAKE = make

# COMPILER
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3
CCFLAGS = -Wall -Wextra -Werror

CCFLAGS += -D WIN_H=500 -D WIN_W=720
CCFLAGS += -D WIN_H=1080 -D WIN_W=720

CFLAGS += -D BUFFER_SIZE=10

CFLAGS += -O3
CCFLAGS += -O3

CFLAGS += -I ./$(LFT_DIR)/inc -I ./$(LMLX_DIR) -I ./inc

LDFLAGS = -L ./

CFLAGS += $(DCOLORS)
CCFLAGS += $(DCOLORS)

# LIBS
LFT = $(LFT_DIR)/$(LFT_NAME)
LMLX = $(LMLX_DIR)/$(LMLX_NAME)

# PATHS
INC_PATH = incs
SRC_PATH = srcs
OBJ_PATH = objs
LIB_PATH = libs

# LIBS DIR
LFT_DIR = $(LIB_PATH)/libft

LMLX_DIR_LINUX = $(LIB_PATH)/mlx_linux
LMLX_DIR_MMS = $(LIB_PATH)/mlx_mms
LMLX_DIR_MACOS_SIERRA = $(LIB_PATH)/minilibx_macos

# SOURCES
SRC_FILES =	colors.c	draw.c	error_utils.c	hooks.c\
		map_utils.c	mlx_utils.c	controls.c	draw_utils.c\
		free.c	main.c	mlx_main.c	handler.c	bresenham_utils.c
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_FILES))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX
	LDLIBS = -lft -lmlx_Linux
	LDLIBS += -lXext -lX11 -lm -lz
	LMLX_NAME = $(LMLX_NAME_LINUX)
	LMLX_DIR = $(LMLX_DIR_LINUX)
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D OSX
	CCFLAGS += -framework OpenGL -framework AppKit
	LDLIBS = -lft -lmlx
	LMLX_NAME = $(LMLX_NAME_MACOS_SIERRA)
	LMLX_DIR = $(LMLX_DIR_MACOS_SIERRA)
endif

all: $(NAME) $(CHECKER_NAME)

$(NAME): $(LFT_NAME) $(LMLX_NAME) $(OBJ)
	$(CC) $^ -o $@ $(CCFLAGS) $(LDFLAGS) $(LDLIBS)

$(LFT_NAME):
	$(MAKE) all -sC $(LFT_DIR)
	cp $(LFT) $(LFT_NAME)

$(LMLX_NAME):
	$(MAKE) all -sC $(LMLX_DIR) 2> /dev/null
	cp $(LMLX) $(LMLX_NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2> /dev/null

clean:
	$(MAKE) clean -sC $(LFT_DIR)
	$(MAKE) clean -sC $(LMLX_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(LMLX_NAME)
	rm -rf $(OBJ_PATH)

fclean: clean
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re norm
