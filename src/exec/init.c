/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:35:28 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 14:22:44 by tle-dref         ###   ########.fr       */
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

void	init_map(t_game *game)
{
	int		i;
	char	*map[] = {"11111111111", "1E000010001", "10000010001",
			"10000010001", "10000000001", "11111111111", NULL};

	i = 0;
	game->map = malloc(sizeof(char *) * 7);
	while (map[i])
	{
		game->map[i] = ft_strdup(map[i]);
		i++;
	}
	game->map[i] = NULL;
}

void	init_textures(t_game *game)
{
	game->textures.n = mlx_load_png("textures/maxborde.png");
	game->textures.s = mlx_load_png("textures/albillie.png");
	game->textures.w = mlx_load_png("textures/gletilly.png");
	game->textures.e = mlx_load_png("textures/lgalloux.png");
	game->ceiling.r = 173;
	game->ceiling.g = 216;
	game->ceiling.b = 230;
	game->floor.r = 120;
	game->floor.g = 120;
	game->floor.b = 120;
}

void		init_player(t_game *game)
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

t_game	*init_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	init_window(game);
	init_map(game);
	init_textures(game);
	init_player(game);
	init_ray(game);
	return (game);
}
