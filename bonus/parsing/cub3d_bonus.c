/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 10:55:43 by aalrofat          #+#    #+#             */
/*   Updated: 2026/09/17 10:55:43 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static	int	validate_argv1(char *str)
{
	int		len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (str[len - 4] == '.' && str[len - 3] == 'c'
		&& str[len - 2] == 'u' && str[len - 1] == 'b')
	{
		return (1);
	}
	return (0);
}

static	void	init_map_struct(t_map *map)
{
	map->map = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->e_texture = NULL;
	map->w_texture = NULL;
	map->f_color = -1;
	map->c_color = -1;
	map->rows = 0;
	map->cols = 0;
	map->player_dir = '\0';
	map->player_x = -1;
	map->player_y = -1;
	map->found_empty_line = 0;
	map->current_line = NULL;
}

static	void	open_file(t_map *map, char *map_name)
{
	char	*line;

	map->fd = open(map_name, O_RDONLY);
	if (map->fd == -1)
		error_message("Open Mapfile Failed", NULL);
	line = get_next_line(map->fd);
	while (line != NULL)
	{
		map->current_line = line;
		parse_line(line, map);
		free(line);
		map->current_line = NULL;
		line = get_next_line(map->fd);
	}
	close(map->fd);
	map->fd = -1;
}

static void	setup_player_and_map(t_game *game)
{
	game->map = game->parse.map;
	game->player_x = (game->parse.player_x * PIXEL_BLOCK_SIZE)
		+ (PIXEL_BLOCK_SIZE / 2.0);
	game->player_y = (game->parse.player_y * PIXEL_BLOCK_SIZE)
		+ (PIXEL_BLOCK_SIZE / 2.0);
	if (game->parse.player_dir == 'E')
		game->angle = 0.0;
	else if (game->parse.player_dir == 'S')
		game->angle = 90.0;
	else if (game->parse.player_dir == 'W')
		game->angle = 180.0;
	else if (game->parse.player_dir == 'N')
		game->angle = 270.0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_message("Wrong arguments. Use: ./cub3D maps/mapname.cub", NULL);
	if (!validate_argv1(argv[1]))
		error_message("Wrong Namefile. Map file must end with .cub", NULL);
	init_map_struct(&game.parse);
	init_game_struct(&game);
	open_file(&game.parse, argv[1]);
	map_dimention(&game.parse);
	parse_map_char(&game.parse);
	map_have_walls(&game.parse);
	setup_player_and_map(&game);
	init_window(&game);
	update_screen(&game);
	mlx_hook(game.mlx_window, 17, 0, close_window_x, &game);
	mlx_hook(game.mlx_window, 2, 1L << 0, key_press_flag, &game);
	mlx_hook(game.mlx_window, 3, 1L << 1, key_release_flag, &game);
	mlx_hook(game.mlx_window, 6, 1L << 6, mouse_move, &game);
	mlx_loop_hook(game.mlx, update_screen, &game);
	mlx_loop(game.mlx);
	return (0);
}
