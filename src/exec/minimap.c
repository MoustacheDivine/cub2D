/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:58 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/13 14:15:22 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mini_square(t_game *game, int size)
{
	int		i;
	int		j;
	t_draw	dr;

	dr = game->draw;
	i = 10;
	while (i < size + 10)
	{
		j = 10;
		while (j < size + 10)
		{
			mlx_put_pixel(game->img, dr.new_x + i, dr.new_y + j, dr.color);
			j++;
		}
		i++;
	}
}

int	calculate_minimap_scale(t_game *game)
{
	int	max_map_size;
	int	scale;

	max_map_size = game->map_width;
	scale = 200 / max_map_size;
	if (scale < 1)
		scale = 1;
	return (scale);
}

void	draw_loop(t_game *game, int scale, int offset_x, int offset_y)
{
	game->draw.i = 0;
	while (game->map[game->draw.i])
	{
		game->draw.j = 0;
		while (game->map[game->draw.i][game->draw.j])
		{
			game->draw.new_x = game->draw.j * scale + offset_x;
			game->draw.new_y = game->draw.i * scale + offset_y;
			if (game->map[game->draw.i][game->draw.j] == '1')
				game->draw.color = create_rgb(100, 100, 100);
			else if (game->map[game->draw.i][game->draw.j] == 'D')
				game->draw.color = create_rgb(255, 110, 50);
			else if (game->map[game->draw.i][game->draw.j] == 'O')
				game->draw.color = create_rgb(0, 250, 0);
			else if (game->map[game->draw.i][game->draw.j] == '0')
				game->draw.color = create_rgb(200, 200, 200);
			else
				game->draw.color = create_rgb(200, 200, 200);
			draw_mini_square(game, scale);
			game->draw.j++;
		}
		game->draw.i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	scale;
	int	offset_x;
	int	offset_y;

	scale = calculate_minimap_scale(game);
	offset_x = 10;
	offset_y = 10;
	draw_loop(game, scale, offset_x, offset_y);
	game->draw.new_x = (int)(game->player.x * scale + offset_x - scale / 2);
	game->draw.new_y = (int)(game->player.y * scale + offset_y - scale / 2);
	game->draw.color = create_rgb(255, 0, 0);
	if (scale == 1)
		scale = 3;
	draw_mini_square(game, scale);
}
