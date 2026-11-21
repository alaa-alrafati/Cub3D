/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_torch_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 00:15:54 by hsbeh             #+#    #+#             */
/*   Updated: 2026/11/14 11:21:36 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	put_torch_pixels(t_game *game, t_texture_img *torch,
	int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < torch->height)
	{
		x = 0;
		while (x < torch->width)
		{
			color = get_pixel_from_img(torch, x, y);
			if (color != 0x000000)
				draw_pixel(game, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_animated_torch(t_game *game)
{
	t_texture_img	*current_torch;
	int				start_x;
	int				start_y;

	if (game->frame_count < 10)
		current_torch = &game->torch_textures[0];
	else if (game->frame_count < 20)
		current_torch = &game->torch_textures[1];
	else
		current_torch = &game->torch_textures[2];
	start_x = WINDOW_W - current_torch->width - 90;
	start_y = WINDOW_H - current_torch->height + 50;
	put_torch_pixels(game, current_torch, start_x, start_y);
}

static double	get_torch_brightness(double distance)
{
	double	brightness;

	if (distance <= 0.1)
		return (MAX_LIGHT);
	brightness = TORCH_RANGE / distance;
	if (brightness > MAX_LIGHT)
		brightness = MAX_LIGHT;
	if (brightness < MIN_LIGHT)
		brightness = MIN_LIGHT;
	return (brightness);
}

int	apply_torch_shadow(int color, double distance)
{
	unsigned char	*rgb;
	double			brightness;

	brightness = get_torch_brightness(distance);
	rgb = (unsigned char *)&color;
	rgb[0] = (unsigned char)(rgb[0] * brightness * BLUE_WARMTH);
	rgb[1] = (unsigned char)(rgb[1] * brightness * GREEN_WARMTH);
	rgb[2] = (unsigned char)(rgb[2] * brightness);
	return (color);
}
