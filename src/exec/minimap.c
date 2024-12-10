/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:58 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 20:40:44 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_mini_square(t_game *game, int x, int y, int size, int color)
{
	int i, j;
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
	int px, py;
	px = (int)(game->player.x * 5);
	py = (int)(game->player.y * 5);
	draw_mini_square(game, px - 1, py - 1, 3, create_rgb(255, 0, 0));
}

void	draw_minimap(t_game *game)
{
	int	color;

	int map_x, map_y;
	int px, py;

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
