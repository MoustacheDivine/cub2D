/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:53:25 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 08:17:28 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_column(t_game *game, int x)
{
	int wall_height; // Hauteur du mur
	int start_y;     // Début du mur sur l'axe Y
	int end_y;       // Fin du mur sur l'axe Y
	int y;           // Itérateur pour dessiner
	int color;       // Couleur du mur
	// Calcul de la hauteur du mur en fonction de la distance
	wall_height = (int)(HEIGHT / game->ray.wall_dist);
	// Calcul du point de départ et de fin pour dessiner le mur
	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = (HEIGHT / 2) + (wall_height / 2);
	// Limiter les valeurs pour éviter de dessiner en dehors de l'écran
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	// Définir la couleur du mur
	// Les murs horizontaux (side = 1) sont plus sombres pour donner un effet 3D
	if (game->ray.side == 0)
		color = create_rgb(0, 0, 200); // Rouge vif
	else
		color = create_rgb(0, 0, 150); // Rouge plus sombre
	// Dessiner la colonne pixel par pixel
	y = start_y;
	while (y <= end_y)
	{
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

void	draw_floor(t_game *game, int y)
{
	int	x;
	int	color;

	color = create_rgb(game->floor.r, game->floor.g, game->floor.b);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	draw_ceiling(t_game *game)
{
	int	color;
	int	x;
	int	y;

	color = create_rgb(game->ceiling.r, game->ceiling.g, game->ceiling.b);
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
	return (y);
}

void	draw_walls(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_properties(game, x);
		init_dda(&game->ray, &game->player);
		perform_dda(game);
		draw_wall_column(game, x);
		x++;
	}
}

void	draw_game(t_game *game)
{
	int y;

	y = draw_ceiling(game);
	draw_floor(game, y);
	draw_walls(game);
}