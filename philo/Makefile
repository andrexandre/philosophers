END		= \033[0m
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m

RM		= rm -f
NAME	= philo
CFLAGS	= -Wall -Wextra -Werror -g -pthread# -fsanitize=thread

OBJDIR	= objs

SRC		= main.c monitor.c philo_utils.c philo_utils2.c
OBJ		= $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

all:	$(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $^ -o $@
	@echo "$(GREEN)\nPhilo compiled 🛠️\n$(END)"

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@$(RM) $(OBJDIR)/*.o
	@$(RM)r objs
	@echo "some stuff removed"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(GREEN)\nPhilo removed 🗑️\n$(END)"

re:	fclean all

# VAR = 1 800 200 200
# VAR = 5 800 200 200
VAR = 5 800 200 200 7
# VAR = 4 410 200 200
# VAR = 4 310 200 100
# VAR = 4 100

run: ${NAME}
	@./${NAME} ${VAR}

v: ${NAME}
	@valgrind --leak-check=full --show-leak-kinds=all ./${NAME} ${VAR}

vh: ${NAME}
	@valgrind --tool=helgrind --history-level=full ./${NAME} ${VAR}

e: fclean

.PHONY:	all clean fclean re run v e
