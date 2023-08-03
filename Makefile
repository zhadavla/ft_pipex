# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 18:59:24 by vzhadan           #+#    #+#              #
#    Updated: 2023/08/03 18:09:23 by vzhadan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = src

SOURCES = $(wildcard $(SRC_DIR)/*.c)

# CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./lib -lftprintf -lft -ldl -lglfw -pthread -lm
MY_HEADER = ./includes/

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.c=.o)))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -I $(MY_HEADER) $(PRINTF) -c $< -o $@

$(NAME): $(OBJECTS)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all