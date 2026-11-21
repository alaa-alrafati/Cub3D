/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 01:54:01 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 01:44:07 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_math(t_game *game, t_ray *ray, double ray_angle)
{
	double	radian;

	ray->start_x = game->player_x / (double)PIXEL_BLOCK_SIZE;
	ray->start_y = game->player_y / (double)PIXEL_BLOCK_SIZE;
	ray->grid_x = (int)ray->start_x;
	ray->grid_y = (int)ray->start_y;
	radian = ray_angle * (PI / 180.0);
	ray->ray_direction_x = cos(radian);
	ray->ray_direction_y = sin(radian);
	ray->full_step_x = fabs(1.0 / ray->ray_direction_x);
	ray->full_step_y = fabs(1.0 / ray->ray_direction_y);
}

static void	setup_step_x(t_ray *ray)
{
	double	dist_to_edge_x;
	double	dist_inside_block_x;

	dist_inside_block_x = ray->start_x - ray->grid_x;
	if (ray->ray_direction_x < 0)
	{
		ray->next_grid_dir_x = -1;
		dist_to_edge_x = dist_inside_block_x;
	}
	else
	{
		ray->next_grid_dir_x = 1;
		dist_to_edge_x = 1.0 - dist_inside_block_x;
	}
	ray->next_edge_x = dist_to_edge_x * ray->full_step_x;
}

static void	setup_step_y(t_ray *ray)
{
	double	dist_to_edge_y;
	double	dist_inside_block_y;

	dist_inside_block_y = ray->start_y - ray->grid_y;
	if (ray->ray_direction_y < 0)
	{
		ray->next_grid_dir_y = -1;
		dist_to_edge_y = dist_inside_block_y;
	}
	else
	{
		ray->next_grid_dir_y = 1;
		dist_to_edge_y = 1.0 - dist_inside_block_y;
	}
	ray->next_edge_y = dist_to_edge_y * ray->full_step_y;
}

void	setup_first_step(t_ray *ray)
{
	setup_step_x(ray);
	setup_step_y(ray);
}

void	dda_jump(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->next_edge_x < ray->next_edge_y)
		{
			ray->next_edge_x += ray->full_step_x;
			ray->grid_x += ray->next_grid_dir_x;
			ray->hit_vertical = 1;
		}
		else
		{
			ray->next_edge_y += ray->full_step_y;
			ray->grid_y += ray->next_grid_dir_y;
			ray->hit_vertical = 0;
		}
		if (game->map[ray->grid_y][ray->grid_x] == '1')
			break ;
	}
}
