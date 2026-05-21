NAME =		philo
SRCS =		ft_atoi.c ft_putchar_fd.c ft_putstr_fd.c init.c main.c
OBJS =		$(SRCS:.c=.o)
DEPS =		$(OBJS:.o=.d)

CC =		cc
CFLAGS =	-Wall -Wextra -Werror -MMD -MP

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: fclean
	$(MAKE) all CFLAGS="$(CFLAGS) -g"

.PHONY: all clean fclean re debug

-include $(DEPS)