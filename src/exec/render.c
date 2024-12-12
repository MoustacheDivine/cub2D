/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:43:40 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 12:55:53 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_teleport(t_game *game, int index)
// {
// 	int			x;
// 	int			y;
// 	int			dest_x;
// 	int			dest_y;
// 	uint32_t	color;

// 	y = 0;
// 	while (y < (int)game->tp_frames[index]->height)
// 	{
// 		x = 0;
// 		while (x < (int)game->tp_frames[index]->width)
// 		{
// 			dest_x = game->img->width - game->tp_frames[index]->width + x;
// 			dest_y = y;
// 			color = get_texture_pixel(game->tp_frames[index], x, y);
// 			if ((color >> 24) != 0)
// 				mlx_put_pixel(game->img, dest_x, dest_y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	draw_teleport(t_game *game)
{
	mlx_texture_t	*current_frame;
	static int		i = 0;
	static int		j = 0;

	if (game->teleport == 0)
	{
		current_frame = game->tp_frames[0];
		draw_texture(game, current_frame, game->img->width - current_frame->width, 0);
		return ;
	}
	if (i < 0 || i >= NUM_FRAMES)
	{
		printf("Error: invalid frame index: %d\n", i);
		return ;
	}
	if (i % 30 == 0)
	{
		current_frame = game->tp_frames[j % 4];
		if (!current_frame)
		{
			printf("Error: current_frame is NULL (frame %d)\n", i);
			return ;
		}
		draw_texture(game, current_frame, game->img->width - current_frame->width, 0);
		j++;
	}
	else
	{
		current_frame = game->tp_frames[j % 4];
		draw_texture(game, current_frame, game->img->width - current_frame->width, 0);
	}
	i++;
	if (i == NUM_FRAMES)
	{
		game->teleport = 0;
		i = 0;
		j = 0;
	}
}


/*void	draw_teleport(t_game *game)
{
	int			x, y;
	int			dest_x;
	int			dest_y;
	uint32_t	color;
	mlx_texture_t	*current_frame;

	current_frame = game->tp_frames[game->teleport];
	printf("tp = %d\n", game->teleport);
	if (!current_frame)
		return;
	y = 0;
	while (y < (int)current_frame->height)
	{
		x = 0;
		while (x < (int)current_frame->width)
		{
			dest_x = game->img->width - current_frame->width + x;
			dest_y = y;
			color = get_texture_pixel(current_frame, x, y);
			if ((color >> 24) != 0)
				mlx_put_pixel(game->img, dest_x, dest_y, color);
			x++;
		}
		y++;
	}
}*/

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
