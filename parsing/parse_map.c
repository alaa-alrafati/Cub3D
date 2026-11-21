/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:08:56 by aalrofat          #+#    #+#             */
/*   Updated: 2026/09/24 15:08:56 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	continue_parse_char(t_map *map, int y,
	int x, int *count_of_player)
{
	char	index;

	index = map->map[y][x];
	if (index != '1' && index != '0' && index != 'N' && index != 'S'
		&& index != 'W' && index != 'E' && index != ' ')
		error_message("There is wrong char in map", map);
	if (index == 'N' || index == 'S' || index == 'W' || index == 'E')
	{
		(*count_of_player)++;
		map->player_y = y;
		map->player_x = x;
		map->player_dir = index;
	}
}

void	parse_map_char(t_map *map)
{
	int	count_of_player;
	int	y;
	int	x;

	count_of_player = 0;
	if (!map->map || !map->map[0])
		error_message("Map is empty", map);
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->map[y][x] != '\0' && map->map[y][x] != '\n')
		{
			continue_parse_char(map, y, x, &count_of_player);
			x++;
		}
		y++;
	}
	if (count_of_player != 1)
		error_message("The map should have one player", map);
}

void	map_dimention(t_map *map)
{
	int	y;

	if (!map->map || !map->map[0])
		error_message("Map is empty", map);
	y = 0;
	while (map->map[y] != NULL)
	{
		y++;
	}
	map->rows = y;
}
