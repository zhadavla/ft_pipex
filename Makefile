# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 16:53:26 by mnurlybe          #+#    #+#              #
#    Updated: 2023/08/15 16:53:31 by mnurlybe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRC_DIR = src

SOURCES = $(wildcard $(SRC_DIR)/*.c)

CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./libft -lft -ldl -lglfw -pthread -lm
MY_HEADER = ./includes/

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.c=.o)))

.PHONY: all clean fclean re

all: libftcc $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -I $(MY_HEADER) $(PRINTF) -c $< -o $@

$(NAME): $(OBJECTS)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libftcc:
	make -C libft
	
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
