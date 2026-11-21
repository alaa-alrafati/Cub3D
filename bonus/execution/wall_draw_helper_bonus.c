/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_draw_helper_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 20:07:01 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 02:05:01 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_wall_texture(t_game *game, t_ray *ray, int column_x, int *y)
{
	double	texture_step_y;
	double	current_texture_y;
	int		color;

	texture_step_y = (double)ray->selected_texture->height / ray->wall_height;
	current_texture_y = (*y - ray->draw_wall_top_y) * texture_step_y;
	while (*y < ray->draw_wall_bottom_y && *y < WINDOW_H)
	{
		color = get_pixel_from_img(ray->selected_texture, ray->texture_column_x,
				(int)current_texture_y);
		color = apply_torch_shadow(color, ray->straight_distance);
		draw_pixel(game, column_x, *y, color);
		current_texture_y += texture_step_y;
		(*y)++;
	}
}

void	draw_ceiling_wall_floor(t_game *game, t_ray *ray, int column_x)
{
	int		screen_y;

	screen_y = 0;
	while (screen_y < ray->draw_wall_top_y && screen_y < WINDOW_H)
	{
		draw_pixel(game, column_x, screen_y, game->parse.c_color);
		screen_y++;
	}
	draw_wall_texture(game, ray, column_x, &screen_y);
	while (screen_y < WINDOW_H)
	{
		draw_pixel(game, column_x, screen_y, game->parse.f_color);
		screen_y++;
	}
}

void	draw_3d_column(t_game *game, double ray_angle, int column_x)
{
	t_ray	ray;

	init_ray_math(game, &ray, ray_angle);
	setup_first_step(&ray);
	dda_jump(game, &ray);
	get_distance_and_texture(&ray, game);
	find_img_column_x(&ray);
	fix_fisheye(game, &ray, ray_angle);
	calculate_wall_dimensions(&ray);
	draw_ceiling_wall_floor(game, &ray, column_x);
}

void	draw_all_columns(t_game *game)
{
	int		column_x;
	double	ray_angle;
	double	angle_step;

	column_x = 0;
	ray_angle = game->angle - 30.0;
	angle_step = 60.0 / (double)WINDOW_W;
	while (column_x < WINDOW_W)
	{
		draw_3d_column(game, ray_angle, column_x);
		ray_angle += angle_step;
		column_x++;
	}
}
