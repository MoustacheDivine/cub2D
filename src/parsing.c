/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:44:32 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/09 15:32:19 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	isespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static void	parse_texture(char *line, t_game *game, char c)
{
	char	*path;

	path = ft_strtrim(line + 2, " ");
	if (c == 'N')
	{
		game->textures.n = mlx_load_png(path);
	}
	else if (c == 'S')
	{
		game->textures.s = mlx_load_png(path);
	}
	else if (c == 'W')
	{
		game->textures.w = mlx_load_png(path);
	}
	else if (c == 'E')
	{
		game->textures.e = mlx_load_png(path);
	}
	free(path);
}

static void	parse_color(char *line, t_game *game, char c)
{
	char	**colors;
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strtrim(line + 2, " ");
	colors = ft_split(tmp + 2, ',');
	if (c == 'F')
	{
		game->floor.r = ft_atoi(colors[0]);
		game->floor.g = ft_atoi(colors[1]);
		game->floor.b = ft_atoi(colors[2]);
	}
	else if (c == 'C')
	{
		game->ceiling.r = ft_atoi(colors[0]);
		game->ceiling.g = ft_atoi(colors[1]);
		game->ceiling.b = ft_atoi(colors[2]);
	}
	while (colors[++i])
		free(colors);
	free(colors);
	free(tmp);
}

static void	parse_map(char *line, t_game *game, int fd)
{
	char	**map;
	int		count;
	int		i;
	char	*tmp;

	i = 0;
	count = 0;
	tmp = line;
	while ((tmp = get_next_line(fd)) != NULL)
	{
		free(tmp);
		count++;
	}
	free(tmp);
	map = malloc(sizeof(char *) * (count + 1));
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	map[i] = NULL;
	game->map = map;
}

int	parsing(int fd, t_game *game)
{
	char *line;

	line = get_next_line(fd);
	printf("line: %s\n", line);
	while (line != NULL)
	{
		printf("line: %s\n", line);
		while (isespace(*line))
			line++;
		if (ft_strncmp(line, "NO ", 3) == 0)
			parse_texture(line, game, 'N');
		else if (ft_strncmp(line, "SO ", 3) == 0)
			parse_texture(line, game, 'S');
		else if (ft_strncmp(line, "WE ", 3) == 0)
			parse_texture(line, game, 'W');
		else if (ft_strncmp(line, "EA ", 3) == 0)
			parse_texture(line, game, 'E');
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color(line, game, 'F');
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color(line, game, 'C');
		else if (ft_strncmp(line, "1 ", 2) == 0)
			parse_map(line, game, fd);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}