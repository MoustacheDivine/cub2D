/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:44:23 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/11 20:38:35 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_positions(int **positions, int count)
{
	int i = 0;

	while (i < count)
	{
		free(positions[i]);
		i++;
	}
	free(positions);
}

int	generate_random_index(int count)
{
	double current_time;
	int random_index;

	current_time = mlx_get_time();
	random_index = (int)(current_time * 1234.567) % count;
	return (random_index);
}

int	**find_available_positions(t_game *game, int count)
{
	int **positions;
	int map_y = 0;
	int map_x;
	int index = 0;

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
	int count = 0;
	int map_y = 0;
	int map_x;

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

void	teleport_player(t_game *game)
{
	int count;
	int **available_positions;
	int random_index;

	count = count_available_positions(game);
	if (count == 0)
	{
		printf("No available position to teleport.\n");
		return;
	}
	available_positions = find_available_positions(game, count);
	random_index = generate_random_index(count);
	game->player.x = available_positions[random_index][0] + 0.5;
	game->player.y = available_positions[random_index][1] + 0.5;
	free_positions(available_positions, count);
	if (!game->particle_frames[0])
	{
		printf("Error: Particle frames not loaded.\n");
		return;
	}
}
