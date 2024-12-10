/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:04:52 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/10 10:55:48 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MLX42/include/MLX42/MLX42.h"
#include "libft.h"
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720
#define MOVE_SPEED 0.08
#define	ROTA_SPEED 0.05

typedef struct s_ray
{
	double 			camera_x;		// Position du rayon sur le plan caméra (de -1 à 1)
	double 			dir_x;			// Direction X du rayon (calculée pour chaque colonne)
	double 			dir_y;			// Direction Y du rayon (calculée pour chaque colonne)
	int 			map_x;			// Coordonnée X de la grille sur laquelle le rayon est actuellement
	int 			map_y;			// Coordonnée Y de la grille sur laquelle le rayon est actuellement
	int 			step_x;			// Direction à suivre en X (+1 ou -1)
	int 			step_y;			// Direction à suivre en Y (+1 ou -1)
	double 			sidedist_x;		// Distance du point de départ au premier côté vertical
	double 			sidedist_y;		// Distance du point de départ au premier côté horizontal
	double 			deltadist_x;	// Distance entre deux côtés verticaux de la grille
	double 			deltadist_y;	// Distance entre deux côtés horizontaux de la grille
	double 			wall_dist;		// Distance perpendiculaire du joueur au mur touché
	int 			side;			// Indique quel côté du mur a été touché
	int				wall_door;
}					t_ray;

typedef struct s_player
{
	double x;       // Position X du joueur
	double y;       // Position Y du joueur
	double dir_x;   // Direction du joueur en X
	double dir_y;   // Direction du joueur en Y
	double plane_x; // Axe "caméra" X (plan de projection)
	double plane_y; // Axe "caméra" Y (plan de projection)
}					t_player;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_textures
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
}					t_textures;

typedef struct s_wall
{
	int		wall_height;  // Hauteur du mur en pixels
	int		start_y;      // Coordonnée Y de début du mur
	int		end_y;        // Coordonnée Y de fin du mur
	double	tex_pos;      // Position verticale actuelle dans la texture
	double	step;         // Taille du pas entre les pixels dans la texture
}				t_wall;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	t_color			floor;
	t_color			ceiling;
	t_textures		textures;
	t_player		player;
	t_ray			ray;
}					t_game;

// init.c
t_game				*init_game(void);

// colors.c
int					create_rgb(unsigned char r, unsigned char g, unsigned char b);
uint32_t	get_texture_pixel(mlx_texture_t *texture, int tex_x, int tex_y);

// player.c
void	player_N(t_game *game);
void	player_S(t_game *game);
void	player_W(t_game *game);
void	player_E(t_game *game);
void	player_NSWE(t_game *game, int x, int y);

// moves.c
void	rotate_player(t_game *game, double angle);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

// render.c
void	render(void *param);

// draw.c
void	draw_game(t_game *game);

// raycasting.c
void	perform_dda(t_game *game);
void	init_dda(t_ray *ray, t_player *player);
void	calculate_ray_properties(t_game *game, int x);

// walls.c
void	draw_wall_column(t_game *game, int x);