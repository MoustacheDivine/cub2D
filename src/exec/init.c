/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:35:28 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/13 20:32:24 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_colors(t_game *game)
{
	game->ceiling.r = -1;
	game->ceiling.g = -1;
	game->ceiling.b = -1;
	game->floor.r = -1;
	game->floor.g = -1;
	game->floor.b = -1;
	game->textures.n = NULL;
	game->textures.s = NULL;
	game->textures.w = NULL;
	game->textures.e = NULL;
	game->textures.door = NULL;
	game->texturetmp = NULL;
	game->tp_frames[0] = NULL;
	game->particle_frames[0] = NULL;
}

void	init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'W' || game->map[y][x] == 'E')
				player_nswe(game, x, y);
			if (game->map[y][x] == 'N')
				player_n(game);
			if (game->map[y][x] == 'S')
				player_s(game);
			if (game->map[y][x] == 'W')
				player_w(game);
			if (game->map[y][x] == 'E')
				player_e(game);
			x++;
		}
		y++;
	}
}

void	init_ray(t_game *game)
{
	game->ray.camera_x = 0.0;
	game->ray.dir_x = game->player.dir_x;
	game->ray.dir_y = game->player.dir_y;
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
	game->ray.step_x = 0;
	game->ray.step_y = 0;
	game->ray.sidedist_x = 0.0;
	game->ray.sidedist_y = 0.0;
	game->ray.deltadist_x = 0.0;
	game->ray.deltadist_y = 0.0;
	game->ray.wall_dist = 0.0;
	game->ray.side = -1;
	game->ray.wall_door = 0;
}

void	load_tp_frames(t_game *game)
{
	game->tp_frames[0] = mlx_load_png("textures/animation/tp0.png");
	game->tp_frames[1] = mlx_load_png("textures/animation/tp3.png");
	game->tp_frames[2] = mlx_load_png("textures/animation/tp2.png");
	game->tp_frames[3] = mlx_load_png("textures/animation/tp1.png");
	if (!game->tp_frames[0] || !game->tp_frames[1] || !game->tp_frames[2]
		|| !game->tp_frames[3])
	{
		clean_game(game);
		exit(1);
	}
}

t_game	*init_game(char *path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->map = NULL;
	game->mlx = NULL;
	game->img = NULL;
	game->tmp2 = NULL;
	game->line = NULL;
	game->path = NULL;
	game->player.x = -1;
	game->player.y = -1;
	init_colors(game);
	parsing(path, game);
	init_window(game);
	init_player(game);
	init_ray(game);
	game->textures.door = mlx_load_png("textures/door.png");
	if (!game->textures.door)
	{
		clean_game(game);
		exit(1);
	}
	game->teleport = 0;
	load_particle_frames(game);
	load_tp_frames(game);
	return (game);
}
