# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alisseye <alisseye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 18:25:25 by alisseye          #+#    #+#              #
#    Updated: 2025/08/31 21:23:41 by alisseye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/main.c srcs/sim.c srcs/init.c srcs/utils.c \
	srcs/parse.c srcs/philo.c srcs/philo_utils.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I includes

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ -I includes

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
	