/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_and_close.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:36:56 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/10 19:37:20 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_error_msg(char *error_msg)
{
	if (error_msg != NULL)
		ft_putendl_fd(error_msg, 2);
}

void	close_game(t_game *game, char *error_msg)
{
	print_error_msg(error_msg);
	free_all(&game->parse);
	if (game->north_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->north_texture.img_ptr);
	if (game->south_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->south_texture.img_ptr);
	if (game->west_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->west_texture.img_ptr);
	if (game->east_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->east_texture.img_ptr);
	if (game->img != NULL)
		mlx_destroy_image(game->mlx, game->img);
	if (game->mlx_window != NULL)
		mlx_destroy_window(game->mlx, game->mlx_window);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (error_msg != NULL)
		exit (1);
	else
		exit(0);
}

int	close_window_x(t_game *game)
{
	ft_putendl_fd("You closed the game by clicking the X button", 1);
	close_game(game, NULL);
	return (0);
}
