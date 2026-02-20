NAME = minishell

CC = cc
#libc readline function leaks. To suppress these leaks run with --suppressions=readline.supp
#don't use fsanitize with valgrind

CFLAGS = -Wall -Wextra -Werror -g #delete g flag
#CFLAGS = -Wall -Wextra -Werror -g3 -O0 -fsanitize=address,undefined -fno-omit-frame-pointer

#FILES
PARSER_DIR = parser/
PARSER_SRC = $(PARSER_DIR)lexer.c

UTILS_DIR = utils/
UTILS_SRC = $(UTILS_DIR)utils.c \
	$(UTILS_DIR)free.c

BUILTINS_DIR = builtins/
BUILTINS_SRC = $(BUILTINS_DIR)env.c

#EXEC_DIR = exec/
#EXEC_SRC = $(EXEC_DIR)

SRCS = main.c $(PARSER_SRC) $(UTILS_SRC) $(BUILTINS_SRC) #$(EXEC_SRC)

OBJS = $(SRCS:.c=.o)

HEADERS = minishell.h \
	parser/parser.h \
	exec/exec.h \
	builtins/builtins.h \
	utils/utils.h

#LIBRARIES
LIBRL = -lreadline
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

#RULES
%.o: %.c $(HEADERS)
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

#VALGRIND
VG = valgrind
VG_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes\
	--child-silent-after-fork=yes --track-fds=yes --suppressions=readline.supp -s

valgrind: $(NAME)
	$(VG) $(VG_FLAGS) ./$(NAME)

.PHONY: all clean fclean re valgrind