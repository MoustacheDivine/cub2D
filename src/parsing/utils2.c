/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:33:17 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 13:44:26 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_end(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (game->map[i])
		i++;
	while (--i)
	{
		if (game->map[i][0] != '1' && game->map[i][0] != ' '
			&& game->map[i][0] != '0' && game->map[i][0] != '\n')
		{
			printf("Error\nmap not at the end\n");
			while (game->map[j])
				free(game->map[j++]);
			free(game->map);
			exit(1);
		}
	}
}

void	check_all_data(t_game *game)
{
	if (!game->textures.n || !game->textures.s || !game->textures.w
		|| !game->textures.e)
	{
		printf("Error\nMissing texture\n");
		exit(1);
	}
	if (game->floor.r < 0 || game->floor.g < 0 || game->floor.b < 0)
	{
		printf("Error\nMissing floor color\n");
		exit(1);
	}
	if (game->ceiling.r < 0 || game->ceiling.g < 0 || game->ceiling.b < 0)
	{
		printf("Error\nMissing ceiling color\n");
		exit(1);
	}
}

int	get_map_len(char *line, int fd, char *file)
{
	int	count;

	count = 0;
	while (line && ft_strcmp(line, "\n") != 0)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	open(file, O_RDONLY);
	return (count);
}

void	get_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				game->player.x = j;
				game->player.y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**cpy_map(t_game *game)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (ft_tablen(game->map) + 1));
	while (game->map[i])
	{
		map[i] = ft_strdup(game->map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

int isvalidchar(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

void	validate_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!isvalidchar(game->map[i][j]) && game->map[i][j] != '\n')
			{
				printf("Error\nInvalid map\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	validate_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= (int)ft_tablen(map)
		|| x >= (int)ft_strlen(map[y]))
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;

	if (map[y][x] == ' ' || !isvalidchar(map[y][x]))
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}

	map[y][x] = 'x';

	validate_flood_fill(map, x - 1, y);
	validate_flood_fill(map, x + 1, y);
	validate_flood_fill(map, x, y - 1);
	validate_flood_fill(map, x, y + 1);
}

void free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void get_player_dir(t_game *game)
{
	if (game->map[(int)game->player.y][(int)game->player.x] == 'N')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (game->map[(int)game->player.y][(int)game->player.x] == 'S')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (game->map[(int)game->player.y][(int)game->player.x] == 'W')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (game->map[(int)game->player.y][(int)game->player.x] == 'E')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
}
