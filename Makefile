# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 18:59:24 by vzhadan           #+#    #+#              #
#    Updated: 2023/08/03 21:49:52 by mnurlybe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = src
BONUS_DIR = bonus

SOURCES = $(wildcard $(SRC_DIR)/*.c)
BONUS = $(wildcard $(BONUS_DIR)/*.c)

# CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./lib -lftprintf -lft -ldl -lglfw -pthread -lm
MY_HEADER = ./includes/

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.c=.o)))
OBJECTS_BONUS = $(addprefix $(OBJ_DIR)/,$(notdir $(BONUS:.c=.o)))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -I $(MY_HEADER) $(PRINTF) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -I $(MY_HEADER) $(PRINTF) -c $< -o $@

$(NAME): $(OBJECTS)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFLAGS)

bonus: $(OBJECTS_BONUS)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS_BONUS) $(LIBFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all