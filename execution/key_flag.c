/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:42:29 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/13 18:16:11 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (0);
}
