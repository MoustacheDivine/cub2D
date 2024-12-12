/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:58 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 06:17:50 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_square(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 10;
	while (i < size + 10)
	{
		j = 10;
		while (j < size + 10)
		{
			mlx_put_pixel(game->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player_on_minimap(t_game *game)
{
	int	px;
	int	py;

	px = (int)(game->player.x * 5);
	py = (int)(game->player.y * 5);
	draw_mini_square(game, px - 1, py - 1, 3, create_rgb(255, 0, 0));
}

void	draw_minimap(t_game *game)
{
	int	color;
	int	map_x;
	int	map_y;
	int	px;
	int	py;

	map_y = 0;
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			px = map_x * 5;
			py = map_y * 5;
			if (game->map[map_y][map_x] == '1')
				color = create_rgb(100, 100, 100);
			else if (game->map[map_y][map_x] == 'D')
				color = create_rgb(255, 110, 50);
			else if (game->map[map_y][map_x] == 'O')
				color = create_rgb(0, 250, 0);
			else if (game->map[map_y][map_x] == '0')
				color = create_rgb(200, 200, 200);
			else
				color = create_rgb(200, 200, 200);
			draw_mini_square(game, px, py, 5, color);
			map_x++;
		}
		map_y++;
	}
	draw_player_on_minimap(game);
}
