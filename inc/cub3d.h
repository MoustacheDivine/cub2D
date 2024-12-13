/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:04:52 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/13 20:32:06 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MLX42/include/MLX42/MLX42.h"
#include "libft.h"
#include <math.h>

#define ERROR_VALUE 2147483648
#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPEED 0.08
#define ROTA_SPEED 0.05
#define T_WIDTH 256
#define NUM_FRAMES 115
#define TP_FRAMES 4
#define MAX_ITER 300

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			wall_dist;
	int				side;
	int				wall_door;
	int				door_open;
}					t_ray;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
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
	mlx_texture_t	*t;
	mlx_texture_t	*door;
}					t_textures;

typedef struct s_wall
{
	int				wall_height;
	int				start_y;
	int				end_y;
	double			tex_pos;
	double			step;
	int				tex_x;
	mlx_texture_t	*texture;
}					t_wall;

typedef struct s_draw
{
	int				color;
	int				i;
	int				j;
	int				new_x;
	int				new_y;
}					t_draw;

typedef struct s_game
{
	mlx_t			*mlx;
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
	mlx_texture_t	*particle_frames[NUM_FRAMES];
	mlx_texture_t	*tp_frames[TP_FRAMES];
	int				current_frame;
	double			animation_time;
	int				teleport;
	t_draw			draw;
	char		*tmp2;
	char		*line;
	char		*path;
	mlx_texture_t	*texturetmp;
}					t_game;

// init.c
t_game				*init_game(char *path);

//init2.c
void	init_window(t_game *game);

// colors.c
int					create_rgb(unsigned char r, unsigned char g,
						unsigned char b);
uint32_t			get_texture_pixel(mlx_texture_t *texture, int tex_x,
						int tex_y);
void				associate_color(t_game *game, char c, t_color rgb);

// player.c
void				player_n(t_game *game);
void				player_s(t_game *game);
void				player_w(t_game *game);
void				player_e(t_game *game);
void				player_nswe(t_game *game, int x, int y);

// moves.c
void				rotate_player(t_game *game, double angle);
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);

// render.c
void				render(void *param);
void				draw_teleport(t_game *game);

// draw.c
void				draw_game(t_game *game);

// raycasting.c
void				perform_dda(t_game *game);
void				init_dda(t_ray *ray, t_player *player);
void				calculate_ray_properties(t_game *game, int x);

// walls.c
void				draw_wall_column(t_game *game, int x);

// parsing
void				parse_color(char *line, t_game *game, char c, char *tofree);
void				parse_texture(char *line, t_game *game, char c);
void				parse_map_loop(int fd, t_game *game, char *line,
						char *file);
int					parsing(char *map, t_game *game);

// utils
void				error_double(int i, t_game *game, char *line);
long				ft_atoi_scam(const char *str);
int					cmp_line(char *tmp, t_game *game);
char				*clean_line(char *line, t_game *game);
int					get_map_len(char *line, int fd, char *file);
void				check_end(t_game *game, char *line, int fd);
void				check_all_data(t_game *game);
void				get_player_pos(t_game *game);
char				**cpy_map(t_game *game);
void				validate_flood_fill(char **map, int x, int y, t_game *game);
void				free_map(char **map);
void				validate_map_chars(t_game *game);
char				**get_back_to_map(char *line, int fd, int count);
int					isvalidchar(char c);
int					ft_tablen(char **tab);

// check.c
int					isvalidchar(char c);
void				check_all(t_game *game);
void				check_all_data(t_game *game);
void				check_double(t_game *game, char c, char *line);
void				check_end(t_game *game, char *line, int fd);

// map.c
char				**cpy_map(t_game *game);
void				get_map_dimension(t_game *game);
int					get_map_len(char *line, int fd, char *file);
void				load_texture(t_game *game, char *path, char c, char *line);
char				**get_back_to_map(char *line, int fd, int count);

// minimap
void				draw_minimap(t_game *game);

// teleport
void				teleport_player(t_game *game);

// particles
void				load_particle_frames(t_game *game);
void				start_particle_animation(t_game *game);
void				draw_particle_animation(t_game *game);
void	draw_texture(t_game *game, mlx_texture_t *src, int x, int y);

// free.c
void				free_positions(int **positions, int count);

// positions.c
int					count_available_positions(t_game *game);
int					**find_available_positions(t_game *game, int count,
						int map_y, int index);

void	clean_game(t_game *game);