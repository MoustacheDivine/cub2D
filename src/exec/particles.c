/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:04:34 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 06:23:29 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_particle_animation(t_game *game)
{
	game->current_frame = 0;
	game->animation_time = mlx_get_time();
}

void	load_particle_frames(t_game *game)
{
	char	**path;
	int		i;
	char	*nb;

	i = 0;
	path = malloc(sizeof(char *) * NUM_FRAMES);
	start_particle_animation(game);
	while (i < NUM_FRAMES)
	{
		nb = ft_itoa(i + 1);
		path[i] = ft_strjoin("./textures/animation/anim", nb);
		free(nb);
		path[i] = clean_join(path[i], ".png");
		game->particle_frames[i] = mlx_load_png(path[i]);
		if (!game->particle_frames[i])
		{
			printf("Failed to load frame: %s\n", path[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	// while(path[i])
	// {
	// 	free(path[i]);
	// 	i++;
	// }
	// free(path);
	game->current_frame = 0;
	game->animation_time = 0.0;
}

/*void	load_tp_frames(t_game *game)
{
	game->tp_frames[0] = mlx_load_png("textures/animation/tp0");
	game->tp_frames[1] = mlx_load_png("textures/animation/tp1");
	game->tp_frames[2] = mlx_load_png("textures/animation/tp2");
	game->tp_frames[3] = mlx_load_png("textures/animation/tp3");
}*/

void	update_particle_animation(t_game *game)
{
	double	current_time;

	current_time = mlx_get_time();
	if (current_time - game->animation_time >= 0.05)
	{
		game->current_frame++;
		game->animation_time = current_time;
		if (game->current_frame >= NUM_FRAMES)
		{
			game->current_frame = -1;
		}
	}
}

void	draw_texture(mlx_image_t *dest, mlx_texture_t *src, int x, int y)
{
	int	*pixels;
	int	color;
	int	i;
	int	j;
	int	dest_x;
	int	dest_y;

	pixels = (int *)src->pixels;
	j = 0;
	while (j < (int)src->height)
	{
		i = 0;
		while (i < (int)src->width)
		{
			dest_x = x + i;
			dest_y = y + j;
			if (dest_x >= 0 && dest_x < (int)dest->width && dest_y >= 0
				&& dest_y < (int)dest->height)
			{
				color = pixels[j * src->width + i];
				if ((color >> 24) != 0)
					mlx_put_pixel(dest, dest_x, dest_y, color);
			}
			i++;
		}
		j++;
	}
}

void	draw_particle_animation(t_game *game)
{
	mlx_texture_t	*current_frame;
	static int		i = 0;

	if (game->teleport == 0)
		return ;
	if (i == 0)
		teleport_player(game);
	if (i < 0 || i >= NUM_FRAMES)
	{
		printf("Error: invalid frame index: %d\n", i);
		return ;
	}
	current_frame = game->particle_frames[i];
	if (!current_frame)
	{
		printf("Error: current_frame is NULL (frame %d)\n", i);
		return ;
	}
	draw_texture(game->img, current_frame, 0, 0);
	i++;
	if (i == NUM_FRAMES)
	{
		game->teleport = 0;
		i = 0;
	}
}
