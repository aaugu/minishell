NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror

INCLUDE = -I includes -I libft
LIB = -Llibft -lft -lreadline
LIBFT = libft/libft.a

LDFLAGS = -L$(HOME)/.brew/opt/readline/lib
CPPFLAGS = -I$(HOME)/.brew/opt/readline/include

RM = rm -f

SRCS_FILES = 	main.c \
				tools/signal.c \
				tools/utils.c \
				built/builtins.c\
				built/cd.c\
				built/echo.c\
				built/export.c\
				built/pwd.c\
				exec/child.c \
				exec/cmd.c \
				exec/count.c \
				exec/error.c \
				exec/exec.c \
				exec/file.c \
				exec/heredoc.c \
				exec/path.c \
				exec/pipe.c \
				free/clear_tokens.c \
				parsing/parsing.c \
                parsing/state_machine.c \
                parsing/state_machine_utils.c \
                parsing/state_less.c \
                parsing/state_greater.c \
                parsing/state_idle.c \
                parsing/state_pipe.c \
                parsing/state_quotes.c \
                parsing/actions_finish.c \
                parsing/actions_modify.c \
                parsing/lists_utils.c \
				parsing/parsing_error.c \

SRCS = $(addprefix ./src/, $(SRCS_FILES))
OBJS = $(SRCS:%.c=%.o)

%.o : %.c
			@$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@echo " [ .. ] | Compiling minishell.."
			@($(CC) $(FLAGS) $(INCLUDE) $(OBJS) $(LIB) $(LDFLAGS) $(CPPFLAGS) -o $(NAME))
			@echo " [ OK ] | minishell ready!"

$(LIBFT):
			@echo " [ .. ] | Compiling libft.."
			@make -s -C libft
			@echo " [ OK ] | Libft ready!"

clean:
			@echo " [ .. ] | Cleaning objects.."
			@make -s -C libft clean
			@($(RM) $(OBJS))
			@echo " [ OK ] | Objects removed!"

fclean: 	clean
			@echo " [ .. ] | Cleaning libraries and executable.."
			@make -s -C libft fclean
			@($(RM) $(NAME))
			@echo " [ OK ] | Everything is clean!"

re: 		fclean all

.PHONY:		all clean fclean re
