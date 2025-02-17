CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = mandatory/main.c mandatory/open.c mandatory/path.c mandatory/pipe.c mandatory/utils.c mandatory/cmd_split.c
OBJ = $(SRCS:.c=.o)

BONUS_SRCS = bonus/main_bonus.c bonus/open_bonus.c mandatory/path.c bonus/utils_bonus.c mandatory/cmd_split.c
BONUS_OBJ = $(BONUS_SRCS:.c=.o)

NAME = pipex
BONUS_NAME = pipex_bonus

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus