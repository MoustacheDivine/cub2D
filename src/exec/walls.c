/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:36:24 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/12 06:53:37 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_pixels(t_game *game, int x, t_wall *wall)
{
	int	y;
	int	tex_y;
	int	color;

	y = wall->start_y;
	while (y <= wall->end_y)
	{
		tex_y = (int)wall->tex_pos % wall->texture->height;
		wall->tex_pos += wall->step;
		color = get_texture_pixel(wall->texture, wall->tex_x, tex_y);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

void	initialize_texture_mapping(t_wall *wall)
{
	wall->step = (double)wall->texture->height / wall->wall_height;
	wall->tex_pos = (wall->start_y - HEIGHT / 2 + wall->wall_height / 2)
		* wall->step;
}

mlx_texture_t	*select_wall_texture(t_game *game)
{
	if (game->ray.wall_door == 1)
		return (game->textures.door);
	else if (game->ray.side == 0)
	{
		if (game->ray.dir_x > 0)
			return (game->textures.e);
		else
			return (game->textures.w);
	}
	else
	{
		if (game->ray.dir_y > 0)
			return (game->textures.s);
		else
			return (game->textures.n);
	}
}

void	calculate_wall_dimensions(t_game *game, t_wall *wall)
{
	double	wall_x;

	if (game->ray.side == 0)
		game->ray.wall_dist = (game->ray.map_x - game->player.x + (1
					- game->ray.step_x) / 2) / game->ray.dir_x;
	else
		game->ray.wall_dist = (game->ray.map_y - game->player.y + (1
					- game->ray.step_y) / 2) / game->ray.dir_y;
	wall->wall_height = (int)(HEIGHT / game->ray.wall_dist);
	wall->start_y = (HEIGHT / 2) - (wall->wall_height / 2);
	wall->end_y = (HEIGHT / 2) + (wall->wall_height / 2);
	if (wall->start_y < 0)
		wall->start_y = 0;
	if (wall->end_y >= HEIGHT)
		wall->end_y = HEIGHT - 1;
	if (game->ray.side == 0)
		wall_x = game->player.y + game->ray.wall_dist * game->ray.dir_y;
	else
		wall_x = game->player.x + game->ray.wall_dist * game->ray.dir_x;
	wall_x -= floor(wall_x);
	wall->tex_x = (int)(wall_x * (double)T_WIDTH);
	if ((game->ray.side == 0 && game->ray.dir_x > 0) || (game->ray.side == 1
			&& game->ray.dir_y < 0))
		wall->tex_x = T_WIDTH - wall->tex_x - 1;
	wall->texture = select_wall_texture(game);
}

void	draw_wall_column(t_game *game, int x)
{
	t_wall	wall;

	calculate_wall_dimensions(game, &wall);
	initialize_texture_mapping(&wall);
	draw_wall_pixels(game, x, &wall);
}
