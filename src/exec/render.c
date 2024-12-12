/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:43:40 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 06:38:18 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_teleport(t_game *game)
{
	int			x;
	int			y;
	int			dest_x;
	int			dest_y;
	uint32_t	color;

	y = 0;
	while (y < (int)game->textures.t->height)
	{
		x = 0;
		while (x < (int)game->textures.t->width)
		{
			dest_x = game->img->width - game->textures.t->width + x;
			dest_y = y;
			color = get_texture_pixel(game->textures.t, x, y);
			if ((color >> 24) != 0)
				mlx_put_pixel(game->img, dest_x, dest_y, color);
			x++;
		}
		y++;
	}
}

void	render(void *param)
{
	t_game		*game;
	static int	i = 0;

	game = (t_game *)param;
	draw_game(game);
	draw_minimap(game);
	draw_teleport(game);
	draw_particle_animation(game);
	if (i == 0)
	{
		mlx_image_to_window(game->mlx, game->img, 0, 0);
		i++;
	}
}
