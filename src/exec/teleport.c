/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:44:23 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 13:08:17 by gbruscan         ###   ########.fr       */
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

int	teleport_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || y >= (int)ft_tablen(map)
		|| x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'x' || map[y][x] == 'D' || map[y][x] == 'O')
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
//	display_map(map);
	return (1);
}

void	exec_teleport(t_game *game, int count, int **av_pos, char ***test_map)
{
	int	random_index;
	int	current_index;

	while (count > 0 && count <= MAX_ITER)
	{
		random_index = generate_random_index(count);
		*test_map = cpy_map(game);
		if (teleport_flood_fill(*test_map, av_pos[random_index][0] + 0.5,
			av_pos[random_index][1] + 0.5))
		{
			game->player.x = av_pos[random_index][0] + 0.5;
			game->player.y = av_pos[random_index][1] + 0.5;
			free_map(*test_map);
			break ;
		}
		free_map(*test_map);
		current_index = 0;
		while (current_index < count - 1)
		{
			av_pos[current_index][0] = av_pos[current_index + 1][0];
			av_pos[current_index][1] = av_pos[current_index + 1][1];
			current_index++;
		}
		count--;
	}
}

void	teleport_player(t_game *game)
{
	int		count;
	int		**av_pos;
	char	**test_map;

	test_map = NULL;
	count = count_available_positions(game);
	if (count == 0)
	{
		printf("No available position to teleport.\n");
		return ;
	}
	av_pos = find_available_positions(game, count, 0, 0);
	exec_teleport(game, count, av_pos, &test_map);
	free_positions(av_pos, count);
	if (!game->particle_frames[0])
	{
		printf("Error: Particle frames not loaded.\n");
		return ;
	}
}
