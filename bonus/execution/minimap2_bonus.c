/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 21:33:07 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 01:37:14 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_the_ray(t_game *game, double x, double y, double radian)
{
	int	pixel_x;
	int	pixel_y;

	while (game->map[(int)y][(int)x] != '1'
		&& game->map[(int)y][(int)x] != ' '
		&& game->map[(int)y][(int)x] != 'D')
	{
		pixel_x = MINI_MAP_OFFSET_X + (int)(x * MINI_MAP_BLOCK_SIZE);
		pixel_y = MINI_MAP_OFFSET_Y + (int)(y * MINI_MAP_BLOCK_SIZE);
		draw_pixel(game, pixel_x, pixel_y, MINI_MAP_RAY_COLOR);
		x += cos(radian) * 0.05;
		if (game->map[(int)y][(int)x] == '1'
			|| game->map[(int)y][(int)x] == ' '
			|| game->map[(int)y][(int)x] == 'D')
			break ;
		y += sin(radian) * 0.05;
		if (game->map[(int)y][(int)x] == '1'
			|| game->map[(int)y][(int)x] == ' '
			|| game->map[(int)y][(int)x] == 'D')
			break ;
	}
}

static void	draw_single_ray(t_game *game, double ray_angle)
{
	double	grid_x;
	double	grid_y;
	double	radian;

	grid_x = game->player_x / PIXEL_BLOCK_SIZE;
	grid_y = game->player_y / PIXEL_BLOCK_SIZE;
	radian = ray_angle * (PI / 180.0);
	draw_the_ray(game, grid_x, grid_y, radian);
}

void	draw_all_rays(t_game *game)
{
	double	current_angle;
	double	end_angle;

	current_angle = game->angle - 30.0;
	end_angle = game->angle + 30.0;
	while (current_angle <= end_angle)
	{
		draw_single_ray(game, current_angle);
		current_angle += 1.0;
	}
}

static void	draw_player_pixels(t_game *game, int center_x, int center_y)
{
	int	x;
	int	y;

	y = center_y - 2;
	while (y <= center_y + 2)
	{
		x = center_x - 2;
		while (x <= center_x + 2)
		{
			draw_pixel(game, x, y, MINI_MAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	double	grid_x;
	double	grid_y;
	int		center_x;
	int		center_y;

	grid_x = game->player_x / PIXEL_BLOCK_SIZE;
	grid_y = game->player_y / PIXEL_BLOCK_SIZE;
	center_x = (int)(grid_x * MINI_MAP_BLOCK_SIZE);
	center_y = (int)(grid_y * MINI_MAP_BLOCK_SIZE);
	center_x += MINI_MAP_OFFSET_X;
	center_y += MINI_MAP_OFFSET_Y;
	draw_player_pixels(game, center_x, center_y);
}
