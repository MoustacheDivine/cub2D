/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:43:40 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 20:33:32 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(void *param)
{
	t_game *game;
	int x;
	static int i = 0;

	game = (t_game *)param;
	x = 0;
	draw_game(game);
	draw_minimap(game);
	if (i == 0)
	{
		mlx_image_to_window(game->mlx, game->img, 0, 0);
		i++;
	}
}