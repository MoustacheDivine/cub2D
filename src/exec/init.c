/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:35:28 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 02:18:28 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		free(game);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		free(game);
		exit(1);
	}
}

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
				player_NSWE(game, x, y);
			if (game->map[y][x] == 'N')
				player_N(game);
			if (game->map[y][x] == 'S')
				player_S(game);
			if (game->map[y][x] == 'W')
				player_W(game);
			if (game->map[y][x] == 'E')
				player_E(game);
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

t_game	*init_game(char *path)
{
	t_game	*game;
  
	game = malloc(sizeof(t_game));
	init_colors(game);
	parsing(path, game);
	init_window(game);
	init_player(game);
	init_ray(game);
	game->textures.door = mlx_load_png("textures/door.png");
	if (!game->textures.door)
	{
		mlx_terminate(game->mlx);
		free(game);
		exit(1);
	}
	game->teleport = 0;
	load_particle_frames(game);
	return (game);
}
