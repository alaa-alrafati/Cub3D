/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 10:55:52 by aalrofat           #+#    #+#            */
/*   Updated: 2026/11/09 16:20:44 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **array)
{
	int	x;

	x = 0;
	if (!array)
		return ;
	while (array[x])
	{
		free(array[x]);
		x++;
	}
	free(array);
}

static	void	check_comma_num(char *line, t_map *map)
{
	int	comma;
	int	x;

	comma = 0;
	x = 0;
	while (line[x] != '\0' && line[x] != '\n')
	{
		if (line[x] == ',')
			comma++;
		x++;
	}
	if (comma != 2)
		error_message("RGB contain more or less than 2 commas", map);
}

void	parse_color(char *line, t_map *map)
{
	char	**split_colors;

	if (!ft_strncmp(line, "F ", 2))
	{
		if (map->f_color != -1)
			error_message("There is already <Floor color>", map);
		check_comma_num(line + 2, map);
		split_colors = ft_split(line + 2, ',');
		if (!split_colors)
			error_message("Split colors failed", map);
		map->f_color = validate_convert_rgb_num(split_colors, map);
		free_split(split_colors);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		if (map->c_color != -1)
			error_message("There is already <Ceiling color>", map);
		check_comma_num(line + 2, map);
		split_colors = ft_split(line + 2, ',');
		if (!split_colors)
			error_message("Split colors failed", map);
		map->c_color = validate_convert_rgb_num(split_colors, map);
		free_split(split_colors);
	}
}
