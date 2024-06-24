NAME = conchita

SRCS 				=	src/parser/environment.c\
						src/parser/token.c \
						src/parser/parse_phases/split_commands.c\
						src/parser/parse_phases/tokenization.c \
						src/parser/parse_phases/expand_token.c \
						src/parser/parse_phases/separate_tokens.c \
						src/parser/parse_phases/create_command.c \
						src/parser/parse_phases/create_input.c \
						src/parser/parse_phases/redirections.c \
						src/parser/parse_phases/expansor.c \
						src/parser/parse_phases/heredoc.c \
						src/parser/parser.c\
						src/parser/variables.c\
						src/parser/quotes.c\
						src/utils/lists.c\
						src/utils/ft_isquote.c\
						src/utils/cleaners.c\
						src/utils/commands.c\
						src/utils/pipes.c\
						src/utils/signals.c\
						src/utils/no_tty_signals.c\
						src/utils/set_qtmark.c\
						src/utils/hd_utils.c\
						src/utils/get_cwd.c\
						src/exec/exec.c\
						src/exec/redirs.c\
						src/builtins/env.c\
						src/builtins/export.c\
						src/builtins/unset.c\
						src/builtins/cd.c\
						src/builtins/echo.c\
						src/builtins/pwd.c\
						src/main.c

OBJS				= $(SRCS:.c=.o)
LIBFT_PATH			= libft
LIBFT_INC_PATH		= $(LIBFT_PATH)/include
LIBFT_LIB_PATH		= $(LIBFT_PATH)/lib
LIBFT_LIB_FILE		= $(LIBFT_LIB_PATH)/libft.a
LIBFT_INC_FLAGS		= -I$(LIBFT_INC_PATH)
LIBFT_LINK_FLAGS	= -L$(LIBFT_LIB_PATH) -lft
CFLAGS 				= $(LIBFT_INC_FLAGS)
CC					= gcc -Wall -Wextra -Werror  -Iincludes

all:	$(NAME)


$(NAME):	$(LIBFT_LIB_FILE) $(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LIBFT_LINK_FLAGS) -lreadline

clean:
	rm -f $(OBJS)
	make -C libft fclean

fclean:	clean
	rm -f $(NAME)

re:		fclean all

deps: $(LIBFT)

$(LIBFT_LIB_FILE):
	make -C libft
