CC = cc
CFLAGS = -Wall -Wextra -Werror

# Mandatory sources
SRCS = mandatory/main.c mandatory/open.c mandatory/path.c mandatory/pipe.c mandatory/utils.c mandatory/cmd_split.c
OBJ = $(SRCS:.c=.o)

# Bonus sources
BONUS_SRCS = bonus/main_bonus.c bonus/open_bonus.c mandatory/path.c bonus/utils_bonus.c mandatory/cmd_split.c
BONUS_OBJ = $(BONUS_SRCS:.c=.o)

# Executable names
NAME = pipex
BONUS_NAME = pipex_bonus

# Libft path
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# Default target (mandatory)
all: $(NAME)

# Bonus target
bonus: $(BONUS_NAME)

# Build libft
$(LIBFT):
	@make -C $(LIBFT_PATH)

# Compile mandatory
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# Compile bonus
$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)

# Rule for object files (applies to both mandatory and bonus)
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

# Clean object files
clean:
	@rm -f $(OBJ) $(BONUS_OBJ)
	@make -C $(LIBFT_PATH) clean

# Full clean (objects + executables)
fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_PATH) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re bonus