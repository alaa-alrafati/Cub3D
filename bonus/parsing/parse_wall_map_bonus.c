/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall_map_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:09:01 by aalrofat          #+#    #+#             */
/*   Updated: 2026/09/24 15:09:01 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static	char	**copy_map(t_map *map)
{
	char	**cpy_map;
	int		y;

	cpy_map = malloc((map->rows + 1) * sizeof(char *));
	if (!cpy_map)
		error_message("cpy_map malloc failed", map);
	y = 0;
	while (y < map->rows)
	{
		cpy_map[y] = ft_strdup(map->map[y]);
		if (!cpy_map[y])
		{
			free_split(cpy_map);
			error_message("cpy_map strdup failed", map);
		}
		y++;
	}
	cpy_map[y] = NULL;
	return (cpy_map);
}

static	void	flood_fill(char **cpy_map, t_map *map, int y, int x)
{
	if (y < 0 || x < 0
		|| y >= map->rows
		|| x >= (int)ft_strlen(cpy_map[y]))
	{
		free_split(cpy_map);
		error_message("We are out of bounds the map", map);
	}
	if (cpy_map[y][x] == ' ' || cpy_map[y][x] == '\n' || cpy_map[y][x] == '\0')
	{
		free_split(cpy_map);
		error_message("We are out of bounds the map", map);
	}
	if (cpy_map[y][x] == '1' || cpy_map[y][x] == 'X')
		return ;
	cpy_map[y][x] = 'X';
	flood_fill(cpy_map, map, y + 1, x);
	flood_fill(cpy_map, map, y - 1, x);
	flood_fill(cpy_map, map, y, x + 1);
	flood_fill(cpy_map, map, y, x - 1);
}

void	map_have_walls(t_map *map)
{
	char	**cpy_map;
	char	index;
	int		y;
	int		x;

	cpy_map = copy_map(map);
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (cpy_map[y][x] != '\0')
		{
			index = cpy_map[y][x];
			if (index == '0' || index == 'N' || index == 'S'
				|| index == 'E' || index == 'W' || index == 'D')
				flood_fill(cpy_map, map, y, x);
			x++;
		}
		y++;
	}
	free_split(cpy_map);
}
