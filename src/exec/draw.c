/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:53:25 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 06:05:11 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_game *game, int y)
{
	int	x;
	int	color;

	color = create_rgb(game->floor.r, game->floor.g, game->floor.b);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	draw_ceiling(t_game *game)
{
	int	color;
	int	x;
	int	y;

	color = create_rgb(game->ceiling.r, game->ceiling.g, game->ceiling.b);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
	return (y);
}

void	draw_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_properties(game, x);
		init_dda(&game->ray, &game->player);
		perform_dda(game);
		draw_wall_column(game, x);
		x++;
	}
}

void	draw_game(t_game *game)
{
	int	y;

	y = draw_ceiling(game);
	draw_floor(game, y);
	draw_walls(game);
}
