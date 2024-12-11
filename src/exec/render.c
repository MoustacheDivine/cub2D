/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:43:40 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/11 20:58:11 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(void *param)
{
	t_game *game;
	game = (t_game *)param;
	static int i = 0;

	draw_game(game);
	draw_minimap(game);
	draw_particle_animation(game);
	if (i == 0)
	{
		mlx_image_to_window(game->mlx, game->img, 0, 0);
		i++;
	}
}