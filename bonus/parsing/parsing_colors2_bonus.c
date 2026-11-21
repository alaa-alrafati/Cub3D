/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 17:46:51 by aalrofat          #+#    #+#             */
/*   Updated: 2026/11/11 00:38:37 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static	int	check_count_digits(char *split_colors)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (split_colors[x] == ' ' || split_colors[x] == '\t')
		x++;
	while (split_colors[x] != '\0' && split_colors[x] != '\n'
		&& ft_isdigit(split_colors[x]))
	{
		count++;
		x++;
	}
	while (split_colors[x] == ' ' || split_colors[x] == '\t')
		x++;
	if (split_colors[x] != '\0' && split_colors[x] != '\n')
		return (-1);
	if (count <= 0)
		return (-1);
	return (count);
}

static	void	cont_validate_convert_rgb(char **split_colors, t_map *map)
{
	if (!split_colors[0] || !split_colors[1] || !split_colors[2]
		|| split_colors[3] != NULL)
	{
		free_split(split_colors);
		error_message("RGB requires exactly 3 numbers", map);
	}
	if (check_count_digits(split_colors[0]) > 3
		|| check_count_digits(split_colors[1]) > 3
		|| check_count_digits(split_colors[2]) > 3
		|| check_count_digits(split_colors[0]) == -1
		|| check_count_digits(split_colors[1]) == -1
		|| check_count_digits(split_colors[2]) == -1)
	{
		free_split(split_colors);
		error_message("Every RGB should cosist from 3 number(0-255)", map);
	}
}

int	validate_convert_rgb_num(char **split_colors, t_map *map)
{
	int	r;
	int	g;
	int	b;

	cont_validate_convert_rgb(split_colors, map);
	r = ft_atoi(split_colors[0]);
	g = ft_atoi(split_colors[1]);
	b = ft_atoi(split_colors[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		free_split(split_colors);
		error_message("RGB should be between <0-255>", map);
	}
	return (r << 16 | g << 8 | b << 0);
}
