/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:43:40 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 15:05:59 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_teleport_animation(t_game *game)
{
	mlx_texture_t	*current_frame;
	static int		i = 1;
	static int		j = 1;

	if (i < 0 || i >= NUM_FRAMES)
		return ;
	if (i % 30 == 0)
	{
		current_frame = game->tp_frames[j % 4];
		j++;
	}
	else
		current_frame = game->tp_frames[j % 4];
	if (!current_frame)
		return ;
	draw_texture(game, current_frame, game->img->width - current_frame->width,
		game->img->height - current_frame->height);
	i++;
	if (i == NUM_FRAMES)
	{
		i = 1;
		j = 0;
	}
}

void	draw_teleport_inactive(t_game *game)
{
	mlx_texture_t	*current_frame;

	current_frame = game->tp_frames[0];
	if (!current_frame)
		return ;
	draw_texture(game, current_frame, game->img->width - current_frame->width,
		0);
}

void	draw_teleport(t_game *game)
{
	if (game->teleport == 0)
		draw_teleport_inactive(game);
	else
		draw_teleport_animation(game);
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
