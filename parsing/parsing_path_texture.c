/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 18:13:20 by aalrofat          #+#    #+#             */
/*   Updated: 2026/11/09 17:52:22 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	open_texture_file(char *path_texture, t_map *map)
{
	int	fd;

	fd = open(path_texture, O_RDONLY);
	if (fd == -1)
	{
		error_message("Path of texture file not found", map);
	}
	close(fd);
}

static	char	*take_path(char *line, t_map *map)
{
	char	*texture_path;
	int		len;

	while (*line != '\0' && (*line == ' ' || *line == '\t'))
		line++;
	len = 0;
	while (line[len] != '\0' && line[len] != ' ' && line[len] != '\t'
		&& line[len] != '\n')
		len++;
	if (len == 0)
		error_message("There is no path", map);
	texture_path = ft_substr(line, 0, len);
	if (!texture_path)
		error_message("Substr texture_path failed", map);
	line = line + len;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line != '\0' && *line != '\n')
	{
		free(texture_path);
		error_message("There is weired char", map);
	}
	return (texture_path);
}

static	void	cont_parse_path_texture(char *line, t_map *map)
{
	int	len;

	if (!ft_strncmp(line, "EA ", 3))
	{
		if (map->e_texture != NULL)
			error_message("There is already <e_texture>", map);
		map->e_texture = take_path(line + 3, map);
		len = ft_strlen(map->e_texture);
		if (len < 5 || (ft_strncmp(map->e_texture + len - 4, ".xpm", 4) != 0))
		{
			error_message("The path should end '.xpm'", map);
		}
		open_texture_file(map->e_texture, map);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (map->w_texture != NULL)
			error_message("There is already <w_texture>", map);
		map->w_texture = take_path(line + 3, map);
		len = ft_strlen(map->w_texture);
		if (len < 5 || (ft_strncmp(map->w_texture + len - 4, ".xpm", 4) != 0))
			error_message("The path should end '.xpm'", map);
		open_texture_file(map->w_texture, map);
	}
}

void	parse_path_texture(char *line, t_map *map)
{
	int	len;

	if (!ft_strncmp(line, "NO ", 3))
	{
		if (map->no_texture != NULL)
			error_message("There is already <NO_texture>", map);
		map->no_texture = take_path(line + 3, map);
		len = ft_strlen(map->no_texture);
		if (len < 5 || (ft_strncmp(map->no_texture + len - 4, ".xpm", 4) != 0))
		{
			error_message("The path should end '.xpm'", map);
		}
		open_texture_file(map->no_texture, map);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (map->so_texture != NULL)
			error_message("There is already <SO_texture>", map);
		map->so_texture = take_path(line + 3, map);
		len = ft_strlen(map->so_texture);
		if (len < 5 || (ft_strncmp(map->so_texture + len - 4, ".xpm", 4) != 0))
			error_message("The path should end '.xpm'", map);
		open_texture_file(map->so_texture, map);
	}
	cont_parse_path_texture(line, map);
}
