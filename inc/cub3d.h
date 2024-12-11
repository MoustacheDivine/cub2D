/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:04:52 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/11 14:58:03 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MLX42/include/MLX42/MLX42.h"
#include "libft.h"
#include <math.h>

#define ERROR_VALUE 2147483648
#define WIDTH 1280
#define HEIGHT 720
#define MOVE_SPEED 0.08
#define ROTA_SPEED 0.05
#define T_WIDTH 256

typedef struct s_ray
{
	double camera_x; // Position du rayon sur le plan caméra (de -1 à 1)
	double dir_x;    // Direction X du rayon (calculée pour chaque colonne)
	double dir_y;    // Direction Y du rayon (calculée pour chaque colonne)
	int				map_x;
	// Coordonnée X de la grille sur laquelle le rayon est actuellement
	int				map_y;
	// Coordonnée Y de la grille sur laquelle le rayon est actuellement
	int step_x;        // Direction à suivre en X (+1 ou -1)
	int step_y;        // Direction à suivre en Y (+1 ou -1)
	double sidedist_x; // Distance du point de départ au premier côté vertical
	double			sidedist_y;
	// Distance du point de départ au premier côté horizontal
	double deltadist_x; // Distance entre deux côtés verticaux de la grille
	double deltadist_y; // Distance entre deux côtés horizontaux de la grille
	double wall_dist;   // Distance perpendiculaire du joueur au mur touché
	int side;           // Indique quel côté du mur a été touché
	int				wall_door;
	int				door_open;
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
	long			r;
	long			g;
	long			b;
}					t_color;

typedef struct s_textures
{
	mlx_texture_t	*n;
	mlx_texture_t	*s;
	mlx_texture_t	*w;
	mlx_texture_t	*e;
	mlx_texture_t	*door;
}					t_textures;

typedef struct s_wall
{
	int wall_height; // Hauteur du mur en pixels
	int start_y;     // Coordonnée Y de début du mur
	int end_y;       // Coordonnée Y de fin du mur
	double tex_pos;  // Position verticale actuelle dans la texture
	double step;     // Taille du pas entre les pixels dans la texture
}					t_wall;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*minimap;
	mlx_image_t		*img;
	char			**map;
	int				map_width;
	int				map_height;
	double			last_time;
	t_color			floor;
	t_color			ceiling;
	t_textures		textures;
	t_player		player;
	t_ray			ray;
}					t_game;

// init.c
t_game				*init_game(char *path);

// colors.c
int					create_rgb(unsigned char r, unsigned char g,
						unsigned char b);
uint32_t			get_texture_pixel(mlx_texture_t *texture, int tex_x,
						int tex_y);

// player.c
void				player_N(t_game *game);
void				player_S(t_game *game);
void				player_W(t_game *game);
void				player_E(t_game *game);
void				player_NSWE(t_game *game, int x, int y);

// moves.c
void				rotate_player(t_game *game, double angle);
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);

// render.c
void				render(void *param);

// draw.c
void				draw_game(t_game *game);

// raycasting.c
void				perform_dda(t_game *game);
void				init_dda(t_ray *ray, t_player *player);
void				calculate_ray_properties(t_game *game, int x);

// walls.c
void				draw_wall_column(t_game *game, int x);

// parsing
void				parse_color(char *line, t_game *game, char c);
void				parse_texture(char *line, t_game *game, char c);
void				load_texture(t_game *game, char *path, char c);
void				parse_map_loop(int fd, t_game *game, char *line,
						char *file);
int					parsing(char *map, t_game *game);
// utils
long				ft_atoi_scam(const char *str);
int					cmp_line(char *tmp, t_game *game);
char				*clean_line(char *line);
void				check_double(t_game *game, char c);
int					get_map_len(char *line, int fd, char *file);
void				check_end(t_game *game, char *line, int fd);
void				check_all_data(t_game *game);
void				get_player_pos(t_game *game);
char				**cpy_map(t_game *game);
void				validate_flood_fill(char **map, int x, int y);
void				free_map(char **map);
void				validate_map_chars(t_game *game);
void				load_texture(t_game *game, char *path, char c);
void				get_back_to_map(char *line, int fd);
int					isvalidchar(char c);
int					ft_tablen(char **tab);

//minimap
void	draw_minimap(t_game *game);


void displaymap(t_game *game);