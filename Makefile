NAME = minishell

CC = cc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -g3 -O0 -fsanitize=address,undefined -fno-omit-frame-pointer #delete it
#CFLAGS = -Wall -Wextra -Werror -g

LIBRL = -lreadline
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a


SRCS = main.c

HEADER = minishell.h

OBJS = $(SRCS:.c=.o)


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBRL) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re