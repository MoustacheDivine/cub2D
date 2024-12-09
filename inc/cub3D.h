/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:09:43 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 00:11:16 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../lib/MLX42/mlx42.h"
#include "../lib/libft/includes/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_VALUE 2147483648

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

typedef struct s_player
{
	int				x;
	int				y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_game
{
	t_color			floor;
	t_color			ceiling;
	t_textures		textures;
	char			**map;
	t_player		player;
}					t_game;

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

// utils2
int					get_map_len(char *line, int fd, char *file);
void				check_end(t_game *game);
void				check_all_data(t_game *game);
void				get_player_pos(t_game *game);
char				**cpy_map(t_game *game);
void				validate_flood_fill(char **map, int x, int y);
void				free_map(char **map);
void				validate_map_chars(t_game *game);
void				get_player_dir(t_game *game);
