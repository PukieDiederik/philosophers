## File stuff

FNAMES 		= philo.c utils.c data.c actions.c

SRCS		= 	$(addprefix $(SRCS_DIR)/,$(FNAMES))

OBJS		= 	$(addprefix $(OBJS_DIR)/,$(FNAMES:.c=.o))

INCLUDE_DIR	= includes
SRCS_DIR	= srcs
OBJS_DIR	= objs

## Compilation

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
INCLUDES	= -I $(INCLUDE_DIR)
LIBS		=
## Other

NAME		= philo
RM			= rm -rf
MAKE		= make -s
# Echo (Different on Linux and Mac)
ifeq ($(shell uname),Linux)
	ECHO	= echo -e
else
	ECHO	= echo
endif


# Colors
BLACK			= \033[0;30m
RED				= \033[0;31m
GREEN			= \033[0;32m
ORANGE			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
GRAY			= \033[0;37m
WHITE			= \033[1;37m
RESET			= \033[0m


## Targets
all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(ECHO) "$(GREEN)>>>>> Compiling $(RESET)$(notdir $<)$(GREEN) -> $(RESET)$(notdir $@)$(RESET)"
	@gcc $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIR):
	@test -d $(OBJS_DIR) || (mkdir $(OBJS_DIR) && $(ECHO) "$(BLUE)Directory '$(CYAN)$(OBJS_DIR)/$(BLUE)' doesn't exist. Creating '$(CYAN)$(OBJS_DIR)/$(BLUE)'$(RESET)")


# regular targets
$(NAME): $(OBJS_DIR) $(OBJS)
	@$(ECHO) "$(GREEN)>>>>> Linking <<<<<$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@$(ECHO) "$(GREEN)>>>>> Cleaning <<<<<$(RESET)"
	$(RM) $(OBJS)

fclean: clean
	@$(ECHO) "Applying full clean"
	@$(RM) $(OBJS_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
