/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:44:23 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 06:43:17 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	generate_random_index(int count)
{
	double	current_time;
	int		random_index;

	current_time = mlx_get_time();
	random_index = (int)(current_time * 1234.567) % count;
	return (random_index);
}

int	**find_available_positions(t_game *game, int count)
{
	int	**positions;
	int	map_y;
	int	map_x;
	int	index;

	map_y = 0;
	index = 0;
	positions = malloc(count * sizeof(int *));
	if (!positions)
		return (NULL);
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			if (game->map[map_y][map_x] == '0')
			{
				positions[index] = malloc(2 * sizeof(int));
				positions[index][0] = map_x;
				positions[index][1] = map_y;
				index++;
			}
			map_x++;
		}
		map_y++;
	}
	return (positions);
}

int	count_available_positions(t_game *game)
{
	int	count;
	int	map_y;
	int	map_x;

	count = 0;
	map_y = 0;
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			if (game->map[map_y][map_x] == '0')
				count++;
			map_x++;
		}
		map_y++;
	}
	return (count);
}

int	teleport_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= (int)ft_tablen(map)
		|| x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (1);
	if (map[y][x] == ' ' || !isvalidchar(map[y][x]))
		return (0);
	map[y][x] = 'x';
	if (teleport_flood_fill(map, x - 1, y) == 0)
		return (0);
	if (teleport_flood_fill(map, x + 1, y) == 0)
		return (0);
	if (teleport_flood_fill(map, x, y - 1) == 0)
		return (0);
	if (teleport_flood_fill(map, x, y + 1) == 0)
		return (0);
	return (1);
}

void	teleport_player(t_game *game)
{
	int		count;
	int		**av_pos;
	int		random_index;
	char	**test_map;
	int		current_index;

	count = count_available_positions(game);
	if (count == 0)
	{
		printf("No available position to teleport.\n");
		return ;
	}
	av_pos = find_available_positions(game, count);
	while (count > 0)
	{
		random_index = generate_random_index(count);
		test_map = cpy_map(game);
		if (teleport_flood_fill(test_map, av_pos[random_index][0] + 0.5,
				av_pos[random_index][1] + 0.5))
		{
			game->player.x = av_pos[random_index][0] + 0.5;
			game->player.y = av_pos[random_index][1] + 0.5;
			free_map(test_map);
			break ;
		}
		free_map(test_map);
		current_index = 0;
		while (current_index < count - 1)
		{
			av_pos[current_index][0] = av_pos[current_index + 1][0];
			av_pos[current_index][1] = av_pos[current_index + 1][1];
			current_index++;
		}
		count--;
	}
	free_positions(av_pos, count);
	if (!game->particle_frames[0])
	{
		printf("Error: Particle frames not loaded.\n");
		return ;
	}
}
