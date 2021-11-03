SRCS = srcs/ft_atoi.c srcs/init.c srcs/main.c srcs/parse.c srcs/philo.c srcs/print.c srcs/free.c

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

$(NAME) : $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


all: $(NAME)

clean: 
		$(RM) $(OBJS)

fclean:
		$(RM) $(OBJS) $(NAME)

re : fclean all