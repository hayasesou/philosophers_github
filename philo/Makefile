NAME = philo


#===FLAGS===#


CFLAGS = -MMD -MP -Wall -Werror -Wextra -g -fsanitize=thread
CC = cc
RM = rm -rf
SRC_DIR = ./srcs
OBJ_DIR = ./objs
D_DIR = ./dir_d
M_FILES = philo_main.c\
		  setting.c\
		  check_argument.c\
		  philo_eat.c\
		  philo_sleep.c\
		  philo_think.c\
		  philo_log.c\
		  philo_life.c\
		  time_stamp.c\
		  philo_take_fork.c\
		  philo_clear.c\
		  print_philo_error.c\
		  philo_utils.c\
		  observe.c\
		  thread.c
INCLUDE_DIR = ./include
INCLUDE = -I$(INCLUDE_DIR)
SRCS = $(addprefix $(SRC_DIR)/,$(M_FILES))
OBJS = $(patsubst $(SRC_DIR)/%c,$(OBJ_DIR)/%o,$(SRCS))
D_FILES = $(patsubst $(SRC_DIR)/%.c,$(D_DIR)/%.d,$(SRCS))
vpath %.c $(SRC_DIR)
vpath %.d $(OBJ_DIR)

#===RULES===#


.PHONY: all
all: $(OBJ_DIR) $(D_DIR) $(NAME)


$(OBJ_DIR):
	mkdir -p $@


$(D_DIR):
	mkdir -p $@

$(NAME): $(OBJS) $(D_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $@


$(D_DIR)/%.d: %.d
	mv $< $(D_DIR)

$(OBJ_DIR)/%.o: %.c ##pattern rule and vpath
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) $(D_DIR)


.PHONY: fclean
fclean: clean
	$(RM) $(NAME)


.PHONY: re
re: fclean all

-include $(D_FILES)
