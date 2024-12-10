/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:43:40 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 07:57:31 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(void *param)
{
	t_game *game;
	int x;

	game = (t_game *)param;
	x = 0;
	draw_game(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}