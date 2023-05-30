NAME		= libft.a


SRC			= ft_abs.c ft_atod.c ft_atoi.c ft_bzero.c ft_calloc.c ft_fibonacci.c \
			  ft_find_next_prime.c ft_get_len.c \
			  ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			  ft_iterative.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
			  ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			  ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
			  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_base_fd.c ft_putnbr_fd.c \
			  ft_putstr_fd.c ft_recursive.c ft_split.c ft_sqrt.c \
			  ft_strchr.c ft_strrev.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			  get_next_line.c \
			  ft_printf.c ft_printf_utils.c ft_print_ptr.c ft_print_unsigned.c ft_print_hex.c \
			  ft_strs_utils.c ft_strcmp.c \

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re