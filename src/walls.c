/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:36:24 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 10:47:20 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_pixels(t_game *game, int x, mlx_texture_t *texture,
		t_wall *wall)
{
	int	y;
	int	tex_y;
	int	color;

	y = wall->start_y;
	while (y <= wall->end_y)
	{
		// Calculer la coordonnée Y dans la texture
		tex_y = (int)wall->tex_pos % texture->height;
		wall->tex_pos += wall->step;
		// Récupérer la couleur depuis la texture
		color = get_texture_pixel(texture, x % texture->width, tex_y);
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

void	calculate_wall_dimensions(t_game *game, t_wall *wall)
{
	wall->wall_height = (int)(HEIGHT / game->ray.wall_dist);
	wall->start_y = (HEIGHT / 2) - (wall->wall_height / 2);
	wall->end_y = (HEIGHT / 2) + (wall->wall_height / 2);
	// Limiter les coordonnées aux bords de l'écran
	if (wall->start_y < 0)
		wall->start_y = 0;
	if (wall->end_y >= HEIGHT)
		wall->end_y = HEIGHT - 1;
}

void	draw_wall_column(t_game *game, int x)
{
	t_wall wall;
	mlx_texture_t *texture;

	// Calculer les dimensions du mur
	calculate_wall_dimensions(game, &wall);

	// Sélectionner la texture appropriée
	texture = select_wall_texture(game);

	// Initialiser le mapping de la texture
	initialize_texture_mapping(texture, &wall);

	// Dessiner les pixels du mur
	draw_wall_pixels(game, x, texture, &wall);
}