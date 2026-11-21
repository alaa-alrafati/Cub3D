/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 02:16:24 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/13 17:08:51 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->mlx_window = NULL;
	game->img = NULL;
	game->first_pixel_ptr = NULL;
	game->north_texture.img_ptr = NULL;
	game->south_texture.img_ptr = NULL;
	game->east_texture.img_ptr = NULL;
	game->west_texture.img_ptr = NULL;
	init_player_movement_struct(game);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		close_game(game, "Error\nin initializing mlx");
	game->mlx_window = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "cub3D");
	if (game->mlx_window == NULL)
		close_game(game, "Error\nin creating window");
	game->img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	if (game->img == NULL)
		close_game(game, "Error\nin creating image");
	game->first_pixel_ptr = (unsigned int *)mlx_get_data_addr(game->img,
			&game->bits_per_pixel, &game->line_len_in_bytes, &game->endian);
	if (game->first_pixel_ptr == NULL)
		close_game(game, "Error\nin getting image data address");
	read_all_sides_texture(game);
}

void	draw_pixel(t_game *game, int x, int y, int color)
{
	int	index;
	int	line_len_in_pixels;

	if (game == NULL || game->first_pixel_ptr == NULL)
		return ;
	if (x < 0 || x >= WINDOW_W || y < 0 || y >= WINDOW_H)
		return ;
	line_len_in_pixels = game->line_len_in_bytes / 4;
	index = (y * line_len_in_pixels) + x;
	game->first_pixel_ptr[index] = color;
}

int	update_screen(t_game *game)
{
	update_player_movement(game);
	draw_all_columns(game);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->img, 0, 0);
	return (0);
}
