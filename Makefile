NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=address

INCLUDE = -I includes -I libft
LIB = -Llibft -lft -lreadline
LIBFT = libft/libft.a

LDFLAGS = -L$(HOME)/.brew/opt/readline/lib
CPPFLAGS = -I$(HOME)/.brew/opt/readline/include

RM = rm -f

SRCS_FILES = 	main.c \
				built-ins/builtins.c\
				built-ins/cd_utils.c\
				built-ins/cd.c\
				built-ins/cmd_env.c \
				built-ins/cmd_exit.c \
				built-ins/cmd_unset.c \
				built-ins/echo.c\
				built-ins/export_utils_1.c\
				built-ins/export_utils_2.c\
				built-ins/export.c\
				built-ins/pwd.c\
				errors/print_error.c \
				exec/child.c \
				exec/cmd.c \
				exec/count.c \
				exec/error_fd.c \
				exec/error.c \
				exec/exec.c \
				exec/file.c \
				exec/heredoc_utils.c \
				exec/heredoc.c \
				exec/path.c \
				exec/pipe.c \
				exec/redir.c \
				free/clear_tokens.c \
				free/clear_minishell.c \
				parsing/meta_interpret.c \
                parsing/parsing-input/actions_finish_buf.c \
				parsing/parsing-input/actions_finish_utils.c \
                parsing/parsing-input/actions_modify.c \
				parsing/parsing-input/parsing_error.c \
				parsing/parsing-input/parsing_input.c \
                parsing/parsing-input/state_greater.c \
                parsing/parsing-input/state_idle.c \
                parsing/parsing-input/state_less.c \
                parsing/parsing-input/state_machine_utils.c \
                parsing/parsing-input/state_machine.c \
                parsing/parsing-input/state_pipe.c \
                parsing/parsing-input/state_quotes.c \
				parsing/parsing-meta/actions.c \
				parsing/parsing-meta/parsing_error_meta.c \
				parsing/parsing-meta/parsing_meta.c \
				parsing/parsing-meta/state_chars.c \
				parsing/parsing-meta/state_dollar.c \
				parsing/parsing-meta/state_idle.c \
				parsing/parsing-meta/state_machine_meta.c \
				tools/signal_inter.c \
				tools/signal_no_inter.c \
				tools/heredoc_signal.c \
				tools/utils.c \

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
