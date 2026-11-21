/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 15:04:12 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 01:34:48 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_block(t_game *game, int start_x, int start_y, int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < MINI_MAP_BLOCK_SIZE - 1)
	{
		pixel_x = 0;
		while (pixel_x < MINI_MAP_BLOCK_SIZE - 1)
		{
			draw_pixel(game, start_x + pixel_x, start_y + pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

static void	draw_map_y(t_game *game, int y, int screen_y)
{
	int	x;
	int	screen_x;

	x = 0;
	while (game->map[y][x] != '\0' && game->map[y][x] != '\n')
	{
		screen_x = x * MINI_MAP_BLOCK_SIZE;
		screen_x += MINI_MAP_OFFSET_X;
		if (game->map[y][x] == '1')
			draw_block(game, screen_x, screen_y, MINI_MAP_WALL_COLOR);
		else if (game->map[y][x] == 'D')
			draw_block(game, screen_x, screen_y, MINI_MAP_DOOR_COLOR);
		x++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	screen_y;

	y = 0;
	while (game->map[y] != NULL)
	{
		screen_y = y * MINI_MAP_BLOCK_SIZE;
		screen_y += MINI_MAP_OFFSET_Y;
		draw_map_y(game, y, screen_y);
		y++;
	}
	draw_all_rays(game);
	draw_player(game);
}
