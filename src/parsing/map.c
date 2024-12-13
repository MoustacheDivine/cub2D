/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:51:07 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/13 16:16:20 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_dimension(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map_width = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
			j++;
		if (j > game->map_width)
			game->map_width = j;
		i++;
	}
	game->map_height = i;
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
	free(line);
	close(fd);
	open(file, O_RDONLY);
	return (count);
}

void	load_texture(t_game *game, char *path, char c, char *line)
{
	void	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		printf("Error\nFailed to load texture\n");
		free(path);
		free(line);
		clean_game(game);
		exit(1);
	}
	if (c == 'N')
	{
		check_double(game, c, line);
		game->textures.n = texture;
	}
	else if (c == 'S')
	{
		check_double(game, c, line);
		game->textures.s = texture;
	}
	else if (c == 'W')
	{
		check_double(game, c, line);
		game->textures.w = texture;
	}
	else if (c == 'E')
	{
		check_double(game, c, line);
		game->textures.e = texture;
	}
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

char	**get_back_to_map(char *line, int fd, int count)
{
	char	*tmp;
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (count + 1));
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (ft_strncmp(tmp, "1", 1) == 0 || ft_strncmp(tmp, "0", 1) == 0)
			break ;
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	while (count > 0 && line)
	{
		map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		count--;
	}
	free(line);
	map[i] = NULL;
	free(tmp);
	return (map);
}
