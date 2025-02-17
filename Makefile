# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 18:25:25 by alisseye          #+#    #+#              #
#    Updated: 2025/02/17 16:42:50 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
$(LIBFT):
	make -C libft bonus -I includes

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ -I includes -I libft

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
	