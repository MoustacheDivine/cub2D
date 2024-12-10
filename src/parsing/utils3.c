/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:48:52 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/10 18:58:14 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static long	loop_scam(int *i, const char *str)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result *= 10;
		result += str[(*i)++] - '0';
	}
	return (result);
}

long	ft_atoi_scam(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	i = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '+' && str[i] != '-' && !ft_isdigit(str[i]))
		return (ERROR_VALUE);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = loop_scam(&i, str);
	result *= sign;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0' && result >= 0 && result <= 255)
		return (result);
	return (ERROR_VALUE);
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

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
