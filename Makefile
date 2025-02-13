NAME				= push_swap

LIBFT				= ./libft/libft.a
INC					= includes/
SRC_DIR				= srcs/
OBJ_DIR				= build/

CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f

SRCS		=	$(SRC_DIR)instructions/push.c \
				$(SRC_DIR)instructions/swap.c \
				$(SRC_DIR)instructions/rev_rotate.c \
				$(SRC_DIR)instructions/rotate.c \
				$(SRC_DIR)push_swap/stack_init.c \
				$(SRC_DIR)push_swap/init_a_to_b.c \
				$(SRC_DIR)push_swap/stack_utils.c \
				$(SRC_DIR)push_swap/stack_cost.c \
				$(SRC_DIR)push_swap/stack.c \
				$(SRC_DIR)push_swap/stack_errors.c \
				$(SRC_DIR)push_swap/stack_sort_biggest.c \


OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

$(LIBFT):
					@make -C ./libft

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)

re: 				fclean all

.PHONY: 			all clean fclean re