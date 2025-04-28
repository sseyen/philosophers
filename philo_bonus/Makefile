NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c srcs/parse.c srcs/init.c \
	srcs/utils.c srcs/sim.c srcs/philo.c \
	srcs/philo_utils.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I includes

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
