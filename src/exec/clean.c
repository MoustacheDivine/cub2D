/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:05:11 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/14 03:56:51 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_textures(t_game *game)
{
	if (game->textures.door)
		mlx_delete_texture(game->textures.door);
	if (game->textures.n)
		mlx_delete_texture(game->textures.n);
	if (game->textures.s)
		mlx_delete_texture(game->textures.s);
	if (game->textures.w)
		mlx_delete_texture(game->textures.w);
	if (game->textures.e)
		mlx_delete_texture(game->textures.e);
}

void	clean_frames(mlx_texture_t **frames, int num_frames)
{
	int	i;

	i = 0;
	while (i < num_frames && frames[i])
	{
		mlx_delete_texture(frames[i]);
		i++;
	}
}

void	clean_game(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	if (game->fd >= 0)
		close(game->fd);
	clean_textures(game);
	clean_frames(game->particle_frames, NUM_FRAMES);
	clean_frames(game->tp_frames, TP_FRAMES);
	free(game);
	exit(0);
}

void	cross_hook(void *param)
{
	t_game	*game;

	game = param;
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (game->map)
		free_map(game->map);
	if (game->fd >= 0)
		close(game->fd);
	clean_textures(game);
	clean_frames(game->particle_frames, NUM_FRAMES);
	clean_frames(game->tp_frames, TP_FRAMES);
	free(game);
	exit(0);
}
