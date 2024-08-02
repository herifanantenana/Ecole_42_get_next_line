# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arakotom <arakotom@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 22:30:59 by arakotom          #+#    #+#              #
#    Updated: 2024/08/03 00:25:32 by arakotom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = objs



SRCS = get_next_line.c \
	get_next_line_utils.c

BONUS_SRCS = get_next_line_bonus.c \
	get_next_line_utils_bonus.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

RM = rm -rf

NAME = get_next_line.a

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) $ -c $< -o $@

bonus: $(BONUS_OBJS)
	ar -rcs $(NAME) $(BONUS_OBJS)

clean :
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
