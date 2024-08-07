
# ---------------------------------- Config ---------------------------------- #
NAME				:= minishell
CC					:= cc
CFLAGS				:= -g -Wall -Wextra -Werror
INCLUDES			:= -I./includes -I/usr/local/Cellar/readline/8.2.10/include
LIBFT_DIR			:= libraries/myLib
LIBFT_LIB			:= $(LIBFT_DIR)/libft.a

ifeq ($(shell uname), Darwin)
	LD_LIB = -L /usr/local/Cellar/readline/8.2.10/lib -lreadline
else ifeq ($(shell uname), Linux)
	LD_LIB = -L/usr/include -lreadline
endif

# --------------------------- Program Source files --------------------------- #
OBJDIR				:= ./objs
VPATH				:= ./src/ ./src/signals/ ./src/builtins/ ./src/executor/ \
						./src/lexer ./src/free/ ./src/utils/ ./src/parser \
						./src/expander/ ./src/error/

SRC					:= main.c
SRC_SIGNALS			:= signals.c signal_utils.c exit_code.c
SRC_FREE			:= env_free.c
SRC_ERROR			:= error_msg.c
SRC_UTILS			:= env_utils.c utils.c env_utils2.c reset_fds.c
SRC_BUILTINS		:= cd.c pwd.c env.c echo.c unset.c exec_builtins.c exit.c export.c
SRC_EXECUTOR		:= executor.c handle_pipe.c command.c heredoc.c files.c command_utils.c
SRC_LEXER			:= lexer.c utils_lexer.c create_token.c
SRC_PARSER			:= parser.c parser_utils.c parser_utils2.c syntax_error.c parser_free.c \
						parser_putargs.c
SRC_EXPANDER		:= expander.c expander_utils.c

SRCS				:= $(SRC) $(SRC_SIGNALS) $(SRC_BUILTINS) $(SRC_EXECUTOR) \
						$(SRC_FREE) $(SRC_UTILS) $(SRC_LEXER) $(SRC_ERROR) \
						$(SRC_EXPANDER) $(SRC_PARSER)

OBJS				:= $(addprefix $(OBJDIR)/, ${SRCS:%.c=%.o})

# ----------------------------------- Rules ---------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LD_LIB) -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -rf objs

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

norm: $(SRCS)
	$(shell norminette | grep Error)

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
