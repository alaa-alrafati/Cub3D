NAME = cub3D
BONUS_NAME = cub3D_bonus
CC = cc

LIBFT_DIR = libft
MLX_DIR = minilibx-linux

INCLUDES = -I. -Ibonus -I$(LIBFT_DIR) -I$(MLX_DIR)
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC = parsing/cub3d.c \
	parsing/parsing_line.c \
	parsing/parsing_colors.c \
	parsing/parsing_colors2.c \
	parsing/parse_map.c \
	parsing/parse_wall_map.c\
	parsing/parsing_path_texture.c \
	parsing/free_error.c \
	execution/create_window.c \
	execution/player_control.c \
	execution/ray_dda.c \
	execution/wall_draw.c \
	execution/from_xpm_to_img.c \
	execution/wall_draw_helper.c \
	execution/key_flag.c \
	execution/clean_up_and_close.c

SRC_BONUS = bonus/parsing/cub3d_bonus.c \
			bonus/parsing/free_error_bonus.c \
			bonus/parsing/parse_map_bonus.c \
			bonus/parsing/parse_wall_map_bonus.c \
			bonus/parsing/parsing_colors_bonus.c \
			bonus/parsing/parsing_colors2_bonus.c \
			bonus/parsing/parsing_line_bonus.c \
			bonus/parsing/parsing_path_texture_bonus.c \
			bonus/execution/create_window_bonus.c \
			bonus/execution/from_xpm_to_img_bonus.c \
			bonus/execution/player_control_bonus.c \
			bonus/execution/ray_dda_bonus.c \
			bonus/execution/wall_draw_bonus.c \
			bonus/execution/wall_draw_helper_bonus.c \
			bonus/execution/key_and_mouse_bonus.c \
			bonus/execution/minimap_bonus.c \
			bonus/execution/minimap2_bonus.c \
			bonus/execution/clean_up_and_close_bonus.c \
			bonus/execution/draw_torch_bonus.c


HEADERFILE = cub3d.h $(LIBFT)
HEADERFILEBONUS = bonus/cub3d_bonus.h

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(MLX) $(LIBFT) $(NAME)

bonus: $(MLX) $(LIBFT) $(BONUS_NAME)

%.o: %.c $(HEADERFILE)
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADERFILEBONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_NAME): $(OBJ_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX_LIBS) -o $(BONUS_NAME)

$(LIBFT) :
		make -C $(LIBFT_DIR)
$(MLX) :
		make -C $(MLX_DIR)

$(NAME) : $(OBJ) $(MLX) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIBS) -o $(NAME)

clean :
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean : clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all bonus clean fclean re
