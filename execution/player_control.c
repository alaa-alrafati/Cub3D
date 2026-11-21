/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 03:16:19 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/13 18:39:46 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_movement_struct(t_game *game)
{
	game->player_movement.move_forward = 0;
	game->player_movement.move_backward = 0;
	game->player_movement.move_left = 0;
	game->player_movement.move_right = 0;
	game->player_movement.rotate_left = 0;
	game->player_movement.rotate_right = 0;
}

static void	move_player(t_game *game, double new_x, double new_y)
{
	int	check_x;
	int	check_y;

	check_x = (int)new_x / PIXEL_BLOCK_SIZE;
	check_y = (int)game->player_y / PIXEL_BLOCK_SIZE;
	if (game->map[check_y][check_x] != '1'
		&& game->map[check_y][check_x] != ' ')
		game->player_x = new_x;
	check_x = (int)(game->player_x / PIXEL_BLOCK_SIZE);
	check_y = (int)(new_y / PIXEL_BLOCK_SIZE);
	if (game->map[check_y][check_x] != '1'
		&& game->map[check_y][check_x] != ' ')
		game->player_y = new_y;
}

static void	side_move(t_game *game, double side_radian, double *x, double *y)
{
	double	move_speed;

	move_speed = 4.0;
	if (game->player_movement.move_right == 1)
	{
		*x += cos(side_radian) * move_speed;
		*y += sin(side_radian) * move_speed;
	}
	if (game->player_movement.move_left == 1)
	{
		*x -= cos(side_radian) * move_speed;
		*y -= sin(side_radian) * move_speed;
	}
}

static void	forward_back_move(t_game *game, double radian, double *x, double *y)
{
	double	move_speed;

	move_speed = 4.0;
	if (game->player_movement.move_forward == 1)
	{
		*x += cos(radian) * move_speed;
		*y += sin(radian) * move_speed;
	}
	if (game->player_movement.move_backward == 1)
	{
		*x -= cos(radian) * move_speed;
		*y -= sin(radian) * move_speed;
	}
}

void	update_player_movement(t_game *game)
{
	double	radian;
	double	new_x;
	double	new_y;
	double	side_radian;

	if (game->player_movement.rotate_left == 1)
		game->angle -= 1.5;
	if (game->player_movement.rotate_right == 1)
		game->angle += 1.5;
	radian = game->angle * (PI / 180.0);
	side_radian = (game->angle + 90.0) * (PI / 180.0);
	new_x = game->player_x;
	new_y = game->player_y;
	forward_back_move(game, radian, &new_x, &new_y);
	side_move(game, side_radian, &new_x, &new_y);
	move_player(game, new_x, new_y);
}
