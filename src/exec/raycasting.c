/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:26:33 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 06:36:31 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_properties(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)WIDTH - 1;
	game->ray.dir_x = game->player.dir_x + game->player.plane_x
		* game->ray.camera_x;
	game->ray.dir_y = game->player.dir_y + game->player.plane_y
		* game->ray.camera_x;
	game->ray.map_x = (int)game->player.x;
	game->ray.map_y = (int)game->player.y;
	game->ray.deltadist_x = fabs(1 / game->ray.dir_x);
	game->ray.deltadist_y = fabs(1 / game->ray.dir_y);
}

void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->y) * ray->deltadist_y;
	}
}

void	ray_wall(t_game *game)
{
	if (game->ray.sidedist_x < game->ray.sidedist_y)
	{
		game->ray.sidedist_x += game->ray.deltadist_x;
		game->ray.map_x += game->ray.step_x;
		game->ray.side = 0;
	}
	else
	{
		game->ray.sidedist_y += game->ray.deltadist_y;
		game->ray.map_y += game->ray.step_y;
		game->ray.side = 1;
	}
}

void	ray_door(t_game *game, int *hit)
{
	if (game->map[game->ray.map_y][game->ray.map_x] == '1')
	{
		game->ray.wall_door = 0;
		*hit = 1;
	}
	else if (game->map[game->ray.map_y][game->ray.map_x] == 'D'
		|| game->map[game->ray.map_y][game->ray.map_x] == 'O')
	{
		if (game->map[game->ray.map_y][game->ray.map_x] == 'D')
		{
			game->ray.wall_door = 1;
			game->ray.door_open = 0;
			*hit = 1;
		}
		else
		{
			game->ray.wall_door = 0;
			game->ray.door_open = 1;
			*hit = 0;
		}
	}
}

void	perform_dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		ray_wall(game);
		ray_door(game, &hit);
	}
	if (game->ray.side == 0)
		game->ray.wall_dist = (game->ray.map_x - game->player.x + (1
					- game->ray.step_x) / 2) / game->ray.dir_x;
	else
		game->ray.wall_dist = (game->ray.map_y - game->player.y + (1
					- game->ray.step_y) / 2) / game->ray.dir_y;
}
