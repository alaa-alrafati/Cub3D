/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_mouse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 14:22:51 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 01:23:30 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	open_close_door(t_game *game)
{
	double	radian;
	double	next_x;
	double	next_y;

	radian = game->angle * (PI / 180.0);
	next_x = game->player_x / PIXEL_BLOCK_SIZE;
	next_y = game->player_y / PIXEL_BLOCK_SIZE;
	next_x += cos(radian);
	next_y += sin(radian);
	if (game->map[(int)next_y][(int)next_x] == 'D')
		game->map[(int)next_y][(int)next_x] = 'O';
	else if (game->map[(int)next_y][(int)next_x] == 'O')
		game->map[(int)next_y][(int)next_x] = 'D';
}

int	key_press_flag(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		ft_putendl_fd("You closed the game with ESC", 1);
		close_game(game, NULL);
	}
	if (keycode == 'w' || keycode == 'W')
		game->player_movement.move_forward = 1;
	if (keycode == 's' || keycode == 'S')
		game->player_movement.move_backward = 1;
	if (keycode == 'a' || keycode == 'A')
		game->player_movement.move_left = 1;
	if (keycode == 'd' || keycode == 'D')
		game->player_movement.move_right = 1;
	if (keycode == 65361)
		game->player_movement.rotate_left = 1;
	if (keycode == 65363)
		game->player_movement.rotate_right = 1;
	return (0);
}

int	key_release_flag(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 'W')
		game->player_movement.move_forward = 0;
	if (keycode == 's' || keycode == 'S')
		game->player_movement.move_backward = 0;
	if (keycode == 'a' || keycode == 'A')
		game->player_movement.move_left = 0;
	if (keycode == 'd' || keycode == 'D')
		game->player_movement.move_right = 0;
	if (keycode == 65361)
		game->player_movement.rotate_left = 0;
	if (keycode == 65363)
		game->player_movement.rotate_right = 0;
	if (keycode == 'k' || keycode == 'K')
		open_close_door(game);
	return (0);
}

int	mouse_move(int current_x, int current_y, t_game *game)
{
	(void)current_y;
	if (current_x > game->player_movement.prev_mouse_x)
		game->angle += 1.5;
	else if (current_x < game->player_movement.prev_mouse_x)
		game->angle -= 1.5;
	game->player_movement.prev_mouse_x = current_x;
	return (0);
}
