NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror

INCLUDE = -I includes -I libft
LIB = -Llibft -lft
LIBFT = libft/libft.a

RM = rm -f

SRCS_FILES = 	main.c \
				parsing/parsing.c \

SRCS = $(addprefix ./src/, $(SRCS_FILES))
OBJS = $(SRCS:%.c=%.o)

%.o : %.c
			@$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@echo " [ .. ] | Compiling minishell.."
			@($(CC) $(FLAGS) $(INCLUDE) $(OBJS) $(LIB) -o $(NAME))
			@echo " [ OK ] | minishell ready!"

$(LIBFT):
			@echo " [ .. ] | Compiling libft.."
			@make -s -C libft
			@echo " [ OK ] | Libft ready!"

clean:
			@echo " [ .. ] | Cleaning objects.."
			@make -s -C libft clean
			@($(RM) $(OBJS) $(BONUS_OBJS))
			@echo " [ OK ] | Objects removed!"

fclean: 	clean
			@echo " [ .. ] | Cleaning libraries and executable.."
			@make -s -C libft fclean
			@($(RM) $(NAME))
			@echo " [ OK ] | Everything is clean!"

re: 		fclean all

.PHONY:		all clean fclean re
