/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:36:24 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 14:10:33 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_pixels(t_game *game, int x, mlx_texture_t *texture, t_wall *wall, int tex_x, double tex_pos, double step)
{
	int y;
	int tex_y;
	int color;

	y = wall->start_y;
	while (y <= wall->end_y)
	{
		// Calculer la coordonnée Y dans la texture
		tex_y = (int)tex_pos % texture->height;
		tex_pos += step;

		// Récupérer la couleur depuis la texture
		color = get_texture_pixel(texture, tex_x, tex_y);

		// Dessiner le pixel
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}


void	initialize_texture_mapping(mlx_texture_t *texture, t_wall *wall)
{
	// Calculer le rapport hauteur texture / mur
	wall->step = (double)texture->height / wall->wall_height;
	// Position initiale dans la texture
	wall->tex_pos = (wall->start_y - HEIGHT / 2 + wall->wall_height / 2)
		* wall->step;
}

mlx_texture_t	*select_wall_texture(t_game *game)
{
	if (game->ray.side == 0)
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

void	calculate_wall_dimensions(t_game *game, t_wall *wall, int *tex_x)
{
	double wall_x;

	// Calcul de la distance perpendiculaire pour éviter la distorsion
	if (game->ray.side == 0)
		game->ray.wall_dist = (game->ray.map_x - game->player.x
				+ (1 - game->ray.step_x) / 2) / game->ray.dir_x;
	else
		game->ray.wall_dist = (game->ray.map_y - game->player.y
				+ (1 - game->ray.step_y) / 2) / game->ray.dir_y;

	// Calcul de la hauteur du mur
	wall->wall_height = (int)(HEIGHT / game->ray.wall_dist);

	// Calcul des limites du mur sur l'écran
	wall->start_y = (HEIGHT / 2) - (wall->wall_height / 2);
	wall->end_y = (HEIGHT / 2) + (wall->wall_height / 2);

	// Limiter les valeurs pour ne pas dessiner hors de l'écran
	if (wall->start_y < 0)
		wall->start_y = 0;
	if (wall->end_y >= HEIGHT)
		wall->end_y = HEIGHT - 1;

	if (game->ray.side == 0)
		wall_x = game->player.y + game->ray.wall_dist * game->ray.dir_y;
	else
		wall_x = game->player.x + game->ray.wall_dist * game->ray.dir_x;
	wall_x -= floor(wall_x);

	*tex_x = (int)(wall_x * (double)T_WIDTH);
	if ((game->ray.side == 0 && game->ray.dir_x > 0) ||
		(game->ray.side == 1 && game->ray.dir_y < 0))
		*tex_x = T_WIDTH - *tex_x - 1;
}


void	draw_wall_column(t_game *game, int x)
{
	t_wall wall;
	int tex_x;
	double tex_pos;
	double step;
	mlx_texture_t *texture;

	// Calculer les dimensions du mur et les coordonnées de la texture
	calculate_wall_dimensions(game, &wall, &tex_x);

	// Sélectionner la texture appropriée
	texture = select_wall_texture(game);

	// Calculer le pas pour mapper la texture
	step = (double)texture->height / wall.wall_height;
	tex_pos = (wall.start_y - HEIGHT / 2 + wall.wall_height / 2) * step;

	// Dessiner chaque pixel du mur
	draw_wall_pixels(game, x, texture, &wall, tex_x, tex_pos, step);
}
