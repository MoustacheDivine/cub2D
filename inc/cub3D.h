/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:09:43 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/09 15:13:53 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../lib/MLX42/mlx42.h"
#include "../lib/libft/includes/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

typedef struct s_game
{
	t_color			floor;
	t_color			ceiling;
	t_textures		textures;
	char			**map;
}			t_game;


//parsing
int	parsing(int fd, t_game *game);
