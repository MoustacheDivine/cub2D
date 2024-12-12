/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:48:53 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/12 06:54:46 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *line, t_game *game, char c)
{
	char	**colors;
	t_color	rgb;

	colors = ft_split(clean_line(line), ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
		(printf("Error\nInvalid color\n"), exit(1));
	rgb.r = ft_atoi_scam(colors[0]);
	rgb.g = ft_atoi_scam(colors[1]);
	rgb.b = ft_atoi_scam(colors[2]);
	if (rgb.r == ERROR_VALUE || rgb.g == ERROR_VALUE || rgb.b == ERROR_VALUE)
		(printf("Error\nInvalid color\n"), exit(1));
	associate_color(game, c, rgb);
}

void	parse_texture(char *line, t_game *game, char c)
{
	char	*path;

	path = clean_line(line);
	load_texture(game, path, c);
	free(path);
}

void	parse_map_loop(int fd, t_game *game, char *line, char *file)
{
	char	**map;
	int		count;

	count = get_map_len(line, fd, file);
	line = get_next_line(fd);
	map = get_back_to_map(line, fd, count);
	line = get_next_line(fd);
	game->map = map;
	check_end(game, line, fd);
}

int	parsing(char *map, t_game *game)
{
	char	*line;
	char	*tmp;
	int		fd;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (ft_strncmp(tmp, "1", 1) != 0 && ft_strncmp(tmp, "0", 1) != 0)
			cmp_line(tmp, game);
		else if (ft_strncmp(tmp, "1", 1) == 0 || ft_strncmp(tmp, "0", 1) == 0)
		{
			parse_map_loop(fd, game, line, map);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_all(game);
	return (0);
}
