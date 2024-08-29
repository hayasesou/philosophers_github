NAME		= philo

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=thread
INCLUDE		= -I./include

SRCS		= srcs/philo_main.c srcs/setting.c srcs/check_argument.c \
			  srcs/philo_eat.c srcs/philo_sleep.c srcs/philo_think.c \
			  srcs/philo_log.c srcs/philo_life.c srcs/time_stamp.c \
			  srcs/philo_take_fork.c srcs/philo_clear.c \
			  srcs/print_philo_error.c srcs/philo_utils.c \
			  srcs/observe.c srcs/thread.c

OBJS		= $(SRCS:srcs/%.c=objs/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

objs/%.o: srcs/%.c
	@mkdir -p objs
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c $< -o $@

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re