CC			= cc
CFLAGS		= -Wextra -Wall -Werror
MLX_LINUX_FLAGS	= -lm -lX11 -lXext
NAME		= fdf
BONUS_NAME	= bonus

LIBFT_PATH	= ./libft/
LIBFT		= $(LIBFT_PATH)libft.a

MLX_PATH	= ./minilibx-linux/
MLX			= $(MLX_PATH)libmlx.a

SRC_PATH 	= srcs/
OBJ_PATH 	= obj/
BONUS_SRC_PATH = ./fdf_bonus/srcs/
BONUS_OBJ_PATH = ./fdf_bonus/obj/

SRC     =   main.c \
			drawing.c \
			drawing_bis.c \
			coordonates.c \
			parsing.c \
			parsing_colors.c

BONUS_SRC	=	main.c \
				parsing.c \
				parsing_colors.c \
				drawing.c \
				coordonates.c \
				gradient_utils.c \
				drawing_bis.c \
				reset.c \
				point_gradient.c \
				line_gradient.c \
				drawing_reverse.c \
				drawing_utils.c \
				drawing_parralel.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
BONUS_SRCS = $(addprefix $(BONUS_SRC_PATH), $(BONUS_SRC))
OBJ		= $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
BONUS_OBJS = $(addprefix $(BONUS_OBJ_PATH), $(BONUS_OBJ))
INCS	= -I ./includes/
BONUS_INCS = -I ./fdf_bonus/includes/

 all: $(OBJ_PATH) $(NAME) $(BONUS_OBJ_PATH) $(BONUS_NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(BONUS_OBJ_PATH)%.o: $(BONUS_SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(BONUS_INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(BONUS_OBJ_PATH):
	mkdir $(BONUS_OBJ_PATH)

$(NAME): $(LIBFT) $(MLX) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_LINUX_FLAGS) -o $(NAME)

$(BONUS_NAME): $(LIBFT) $(MLX) $(BONUS_OBJ_PATH) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX) $(MLX_LINUX_FLAGS) -o $(BONUS_NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX):
	make -C $(MLX_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	rm -rf $(OBJ_PATH)
	rm -rf $(BONUS_OBJ_PATH)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
