/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_and_close_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 01:27:00 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 00:09:37 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	print_error_msg(char *error_msg)
{
	if (error_msg != NULL)
		ft_putendl_fd(error_msg, 2);
}

static void	destroy_all_textures(t_game *game)
{
	int	i;

	if (game->north_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->north_texture.img_ptr);
	if (game->south_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->south_texture.img_ptr);
	if (game->west_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->west_texture.img_ptr);
	if (game->east_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->east_texture.img_ptr);
	if (game->door_texture.img_ptr != NULL)
		mlx_destroy_image(game->mlx, game->door_texture.img_ptr);
	i = 0;
	while (i < 3)
	{
		if (game->torch_textures[i].img_ptr != NULL)
			mlx_destroy_image(game->mlx, game->torch_textures[i].img_ptr);
		i++;
	}
}

void	close_game(t_game *game, char *error_msg)
{
	print_error_msg(error_msg);
	free_all(&game->parse);
	destroy_all_textures(game);
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
		exit(1);
	else
		exit(0);
}

int	close_window_x(t_game *game)
{
	ft_putendl_fd("You closed the game by clicking the X button", 1);
	close_game(game, NULL);
	return (0);
}
