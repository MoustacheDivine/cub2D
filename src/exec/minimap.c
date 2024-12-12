/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:58 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 08:02:24 by gbruscan         ###   ########.fr       */
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

void	draw_player_on_minimap(t_game *game)
{
	game->draw.new_x = (int)(game->player.x * 5 - 1);
	game->draw.new_y = (int)(game->player.y * 5 - 1);
	game->draw.color = create_rgb(255, 0, 0);
	draw_mini_square(game, 3);
}

void	draw_minimap(t_game *game)
{
	game->draw.i = 0;
	while (game->map[game->draw.i])
	{
		game->draw.j = 0;
		while (game->map[game->draw.i][game->draw.j])
		{
			game->draw.new_x = game->draw.j * 5;
			game->draw.new_y = game->draw.i * 5;
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
			draw_mini_square(game, 5);
			game->draw.j++;
		}
		game->draw.i++;
	}
	draw_player_on_minimap(game);
}
