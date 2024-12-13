/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:04:34 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/13 18:55:38 by tle-dref         ###   ########.fr       */
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
			clean_game(game);
			exit(1);
		}
		free(path[i]);
		i++;
	}
	free(path);
	game->current_frame = 0;
	game->animation_time = 0.0;
}

void	draw_texture(t_game *game, mlx_texture_t *src, int x, int y)
{
	mlx_image_t	*dest;
	t_draw		dr;
	uint8_t		*pixel;

	dest = game->img;
	dr = game->draw;
	dr.j = -1;
	while (++dr.j < (int)src->height)
	{
		dr.i = -1;
		while (++dr.i < (int)src->width)
		{
			dr.new_x = x + dr.i;
			dr.new_y = y + dr.j;
			if (dr.new_x >= 0 && dr.new_x < (int)dest->width && dr.new_y >= 0
				&& dr.new_y < (int)dest->height)
			{
				pixel = src->pixels + (dr.j * src->width + dr.i) * 4;
				dr.color = (pixel[3] << 24) | (pixel[0]) | (pixel[1] << 16) | (pixel[2] << 8);
				if ((dr.color >> 24) != 0)
					mlx_put_pixel(dest, dr.new_x, dr.new_y, dr.color);
			}
		}
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
	draw_texture(game, current_frame, 0, 0);
	i++;
	if (i == NUM_FRAMES)
	{
		game->teleport = 0;
		i = 0;
	}
}
