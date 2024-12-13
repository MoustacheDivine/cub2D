/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:31:25 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/13 20:34:30 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cmp_line(char *tmp, t_game *game)
{
	char	*tmp2;
	tmp2 = tmp;
	if (ft_strncmp(tmp, "NO ", 3) == 0)
		parse_texture(tmp + 3, game, 'N');
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		parse_texture(tmp + 3, game, 'S');
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		parse_texture(tmp + 3, game, 'W');
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		parse_texture(tmp + 3, game, 'E');
	else if (ft_strncmp(tmp, "F ", 2) == 0)
		parse_color(tmp + 2, game, 'F', tmp2);
	else if (ft_strncmp(tmp, "C ", 2) == 0)
		parse_color(tmp + 2, game, 'C', tmp2);
	else if (tmp[0] == '\n' || tmp[0] == '\0')
		;
	else
	{
		printf("Error\nInvalid line\n");
		free(game->line);
		free(game->tmp2);
		clean_game(game);
		exit(1);
	}
	return (0);
}

char	*clean_line(char *line, t_game *game)
{
	char	*cleaned;

	if (line[0] == '\n')
	{
		printf("Error\nInvalid line\n");
		clean_game(game);
		exit(1);
	}
	cleaned = ft_strtrim(line, " \n");
	return (cleaned);
}

void	error_double(int i, t_game *game, char *line)
{
	if (i == 1)
	{
		printf("Error\ndouble textures\n");
		if(game->texturetmp)
			mlx_delete_texture(game->texturetmp);
		if(game->path)
			free(game->path);
		free(game->line);
		free(game->tmp2);
		clean_game(game);
		exit(1);
	}
	else if (i == 2)
	{
		printf("Error\ndouble colors\n");
		free(line);
		free(game->line);
		free(game->tmp2);
		clean_game(game);
		exit(1);
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
