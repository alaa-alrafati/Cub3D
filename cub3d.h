/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 10:53:02 by aalrofat          #+#    #+#             */
/*   Updated: 2026/09/17 10:53:02 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define WINDOW_W 1024
# define WINDOW_H 768
# define PIXEL_BLOCK_SIZE 80
# define PI 3.14159265359

typedef struct s_map
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*e_texture;
	char	*w_texture;

	int		f_color;
	int		c_color;

	int		rows;
	int		cols;

	char	player_dir;
	int		player_x;
	int		player_y;
	int		found_empty_line;
	char	*current_line;
	int		fd;
}	t_map;

typedef struct s_texture_img
{
	unsigned int	*first_pixel_ptr;
	void			*img_ptr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_len_in_bytes;
	int				endian;
}	t_texture_img;

typedef struct s_player_movement
{
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
	int		prev_mouse_x;

}	t_player_movement;

typedef struct s_game
{
	void				*mlx;
	void				*mlx_window;
	void				*img;
	unsigned int		*first_pixel_ptr;
	int					bits_per_pixel;
	int					line_len_in_bytes;
	int					endian;
	char				**map;
	double				player_x;
	double				player_y;
	double				angle;

	t_texture_img		north_texture;
	t_texture_img		south_texture;
	t_texture_img		east_texture;
	t_texture_img		west_texture;
	t_player_movement	player_movement;
	t_map				parse;

}	t_game;

typedef struct s_ray
{
	double			start_x;
	double			start_y;
	double			ray_direction_x;
	double			ray_direction_y;
	int				grid_x;
	int				grid_y;
	double			full_step_x;
	double			full_step_y;
	double			next_edge_x;
	double			next_edge_y;
	int				next_grid_dir_x;
	int				next_grid_dir_y;
	int				hit_vertical;
	double			straight_distance;
	double			distance_to_wall;
	int				wall_height;
	int				draw_wall_top_y;
	int				draw_wall_bottom_y;
	int				texture_column_x;
	t_texture_img	*selected_texture;
}	t_ray;

void	parse_line(char *line, t_map *map);
void	parse_path_texture(char *line, t_map *map);
void	parse_color(char *line, t_map *map);
void	free_split(char **array);
void	error_message(char *str, t_map *map);
void	map_dimention(t_map *map);
void	parse_map_char(t_map *map);
void	map_have_walls(t_map *map);
void	free_all(t_map *map);
int		validate_convert_rgb_num(char **split_colors, t_map *map);
int		main(int argc, char **argv);
void	init_window(t_game *game);
void	draw_pixel(t_game *game, int x, int y, int color);
void	close_game(t_game *game, char *error_msg);
int		close_window_x(t_game *game);
void	init_ray_math(t_game *game, t_ray *ray, double ray_angle);
void	setup_first_step(t_ray *ray);
void	dda_jump(t_game *game, t_ray *ray);
void	draw_ceiling_wall_floor(t_game *game, t_ray *ray, int column_x);
void	draw_3d_column(t_game *game, double ray_angle, int column_x);
void	draw_all_columns(t_game *game);
int		update_screen(t_game *game);
void	read_all_sides_texture(t_game *game);
int		get_pixel_from_img(t_texture_img *img, int x, int y);
void	find_img_column_x(t_ray *ray);
void	fix_fisheye(t_game *game, t_ray *ray, double ray_angle);
void	calculate_wall_dimensions(t_ray *ray);
void	get_distance_and_texture(t_ray *ray, t_game *game);
void	update_player_movement(t_game *game);
void	init_player_movement_struct(t_game *game);
int		key_press_flag(int keycode, t_game *game);
int		key_release_flag(int keycode, t_game *game);
void	init_game_struct(t_game *game);

#endif
