/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_xpm_to_img_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 00:28:56 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/13 23:59:41 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	read_xpm(t_game *game, t_texture_img *texture_img, char *xpm_path)
{
	texture_img->img_ptr = mlx_xpm_file_to_image(game->mlx, xpm_path,
			&texture_img->width, &texture_img->height);
	if (texture_img->img_ptr == NULL)
	{
		ft_putstr_fd("Error\n in reading texture image: ", 2);
		close_game(game, xpm_path);
	}
	texture_img->first_pixel_ptr = (unsigned int *)mlx_get_data_addr(
			texture_img->img_ptr, &texture_img->bits_per_pixel,
			&texture_img->line_len_in_bytes, &texture_img->endian);
	if (!texture_img->first_pixel_ptr)
	{
		ft_putstr_fd("Error\n to get pixel data address for texture: ", 2);
		close_game(game, xpm_path);
	}
}

void	read_all_sides_texture(t_game *game)
{
	read_xpm(game, &game->north_texture, game->parse.no_texture);
	read_xpm(game, &game->south_texture, game->parse.so_texture);
	read_xpm(game, &game->west_texture, game->parse.w_texture);
	read_xpm(game, &game->east_texture, game->parse.e_texture);
	read_xpm(game, &game->door_texture, DOOR_PATH);
	read_xpm(game, &game->torch_textures[0], TORCH_PATH_1);
	read_xpm(game, &game->torch_textures[1], TORCH_PATH_2);
	read_xpm(game, &game->torch_textures[2], TORCH_PATH_3);
}

int	get_pixel_from_img(t_texture_img *img, int x, int y)
{
	int	index;
	int	color;
	int	line_len_in_pixels;

	if (x < 0)
		x = 0;
	if (x >= img->width)
		x = img->width - 1;
	if (y < 0)
		y = 0;
	if (y >= img->height)
		y = img->height - 1;
	line_len_in_pixels = img->line_len_in_bytes / 4;
	index = (y * line_len_in_pixels) + x;
	color = img->first_pixel_ptr[index];
	return (color);
}

static void	flip_texture_column(t_ray *ray)
{
	int		last_column;

	last_column = ray->selected_texture->width - 1;
	if (ray->hit_vertical == 1 && ray->ray_direction_x < 0)
		ray->texture_column_x = last_column - ray->texture_column_x;
	if (ray->hit_vertical == 0 && ray->ray_direction_y > 0)
		ray->texture_column_x = last_column - ray->texture_column_x;
}

void	find_img_column_x(t_ray *ray)
{
	double	hit_spot;
	double	texture_width;
	double	ray_distance_to_wall;

	texture_width = (double)ray->selected_texture->width;
	if (ray->hit_vertical == 1)
	{
		ray_distance_to_wall = ray->distance_to_wall * ray->ray_direction_y;
		hit_spot = ray->start_y + ray_distance_to_wall;
	}
	else
	{
		ray_distance_to_wall = ray->distance_to_wall * ray->ray_direction_x;
		hit_spot = ray->start_x + ray_distance_to_wall;
	}
	hit_spot = hit_spot - (int)hit_spot;
	ray->texture_column_x = (int)(hit_spot * texture_width);
	flip_texture_column(ray);
}
