/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:31:25 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 19:26:38 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	isvalidchar(char c)
{
	return (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == '2');
}

int	cmp_line(char *tmp, t_game *game)
{
	if (ft_strncmp(tmp, "NO ", 3) == 0)
		parse_texture(tmp + 3, game, 'N');
	else if (ft_strncmp(tmp, "SO ", 3) == 0)
		parse_texture(tmp + 3, game, 'S');
	else if (ft_strncmp(tmp, "WE ", 3) == 0)
		parse_texture(tmp + 3, game, 'W');
	else if (ft_strncmp(tmp, "EA ", 3) == 0)
		parse_texture(tmp + 3, game, 'E');
	else if (ft_strncmp(tmp, "F ", 2) == 0)
		parse_color(tmp + 2, game, 'F');
	else if (ft_strncmp(tmp, "C ", 2) == 0)
		parse_color(tmp + 2, game, 'C');
	else if (tmp[0] == '\n' || tmp[0] == '\0')
		;
	else
	{
		printf("Error\nInvalid line\n");
		exit(1);
	}
	return (0);
}

char	*clean_line(char *line)
{
	char	*trimmed;
	char	*cleaned;

	cleaned = ft_strtrim(line, "\n");
	trimmed = ft_strtrim(cleaned, " ");
	free(cleaned);
	return (trimmed);
}

void	error_double(int i)
{
	if (i == 1)
	{
		printf("Error\ndouble textures\n");
		exit(1);
	}
	else if (i == 2)
	{
		printf("Error\ndouble colors\n");
		exit(1);
	}
}

void	check_double(t_game *game, char c)
{
	if (c == 'N' && game->textures.n)
		error_double(1);
	else if (c == 'S' && game->textures.s)
		error_double(1);
	else if (c == 'W' && game->textures.w)
		error_double(1);
	else if (c == 'E' && game->textures.e)
		error_double(1);
	else if (c == 'F' && game->floor.r >= 0)
		error_double(2);
	else if (c == 'C' && game->ceiling.r >= 0)
		error_double(2);
}
