/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 12:06:55 by aalrofat          #+#    #+#             */
/*   Updated: 2026/10/04 12:06:55 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	error_message(char *str, t_map *map)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	if (map)
		free_all(map);
	get_next_line(-1);
	exit(1);
}

void	free_all(t_map *map)
{
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->e_texture)
		free(map->e_texture);
	if (map->w_texture)
		free(map->w_texture);
	if (map->current_line)
		free(map->current_line);
	if (map->map)
		free_split(map->map);
	if (map->fd != -1)
	{
		close(map->fd);
		map->fd = -1;
	}
}
