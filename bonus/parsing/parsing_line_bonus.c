/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 10:55:57 by aalrofat          #+#    #+#             */
/*   Updated: 2026/09/17 10:55:57 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static	char	*handle_spaces(char *line)
{
	int	x;

	x = 0;
	while (line[x] != '\0' && (line[x] == ' ' || line[x] == '\t'))
		x++;
	return (&line[x]);
}

static	char	**add_line_to_array(char *line, t_map *map)
{
	char	**new_map;
	int		x;

	x = 0;
	while (map->map != NULL && map->map[x] != NULL)
		x++;
	new_map = malloc((x + 2) * sizeof(char *));
	if (!new_map)
		error_message("Malloc failed for new_map", map);
	x = 0;
	while (map->map != NULL && map->map[x] != NULL)
	{
		new_map[x] = map->map[x];
		x++;
	}
	free(map->map);
	new_map[x] = ft_strdup(line);
	if (!new_map[x])
	{
		free_split(new_map);
		error_message("Strdup of line failed", map);
	}
	new_map[x + 1] = NULL;
	return (new_map);
}

static	void	parse_map_line(char *line, t_map *map)
{
	if (!line)
		return ;
	if (!map->no_texture || !map->so_texture || !map->e_texture
		|| !map->w_texture || map->f_color == -1 || map->c_color == -1)
		error_message("We must read <Path_textures> and <Colors> first", map);
	if (map->found_empty_line == 1)
		error_message("found empty line inside map", map);
	map->map = add_line_to_array(line, map);
}

void	parse_line(char *line, t_map *map)
{
	char	*new_line;

	new_line = handle_spaces(line);
	if (*new_line == '\0' || *new_line == '\n' || *new_line == '\r')
	{
		if (map->map != NULL)
			map->found_empty_line = 1;
		return ;
	}
	if (!ft_strncmp(new_line, "NO ", 3) || !ft_strncmp(new_line, "SO ", 3)
		|| !ft_strncmp(new_line, "EA ", 3) || !ft_strncmp(new_line, "WE ", 3))
		parse_path_texture(new_line, map);
	else if (!ft_strncmp(new_line, "F ", 2) || !ft_strncmp(new_line, "C ", 2))
		parse_color(new_line, map);
	else if (*new_line == '0' || *new_line == '1')
		parse_map_line(line, map);
	else
		error_message("Wrong Charactars in Map!", map);
}
