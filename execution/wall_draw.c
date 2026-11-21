/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 03:19:29 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/13 20:48:22 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_distance_and_texture(t_ray *ray, t_game *game)
{
	if (ray->hit_vertical == 1)
	{
		ray->distance_to_wall = ray->next_edge_x - ray->full_step_x;
		if (ray->ray_direction_x > 0)
			ray->selected_texture = &game->east_texture;
		else
			ray->selected_texture = &game->west_texture;
	}
	else
	{
		ray->distance_to_wall = ray->next_edge_y - ray->full_step_y;
		if (ray->ray_direction_y > 0)
			ray->selected_texture = &game->south_texture;
		else
			ray->selected_texture = &game->north_texture;
	}
}

void	fix_fisheye(t_game *game, t_ray *ray, double ray_angle)
{
	double	ray_tilt_degree;
	double	ray_tilt_radian;

	ray_tilt_degree = ray_angle - game->angle;
	ray_tilt_radian = ray_tilt_degree * (PI / 180.0);
	ray->straight_distance = ray->distance_to_wall * cos(ray_tilt_radian);
}

void	calculate_wall_dimensions(t_ray *ray)
{
	int	screen_center_y;
	int	half_wall_height;

	if (ray->straight_distance <= 0.0)
		ray->wall_height = WINDOW_H;
	else
		ray->wall_height = (int)(WINDOW_H / ray->straight_distance);
	screen_center_y = WINDOW_H / 2;
	half_wall_height = ray->wall_height / 2;
	ray->draw_wall_top_y = screen_center_y - half_wall_height;
	ray->draw_wall_bottom_y = screen_center_y + half_wall_height;
}
