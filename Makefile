CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = mandatory/main.c mandatory/open.c mandatory/path.c mandatory/pipe.c mandatory/utils.c
OBJ = $(SRCS:.c=.o)
NAME = pipex
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re